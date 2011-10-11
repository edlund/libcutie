#!/usr/bin/env python

from __future__ import print_function

import argparse
import json
import os
import re
import subprocess
import sys

class Amalgamation(object):
	
	@staticmethod
	def file_path(file_path, include_paths):
		file_found = os.path.exists(file_path)
		if file_found:
			return file_path
		
		for include_path in include_paths:
			tmp_path = "{0}/{1}".format(include_path, file_path)
			file_found = os.path.exists(tmp_path)
			if file_found:
				return tmp_path
		
		return None
	
	def __init__(self, args):
		with open(args.config, 'r') as f:
			config = json.loads(f.read())
			for key in config:
				setattr(self, key, config[key])
			self.included_files = []
	
	def generate(self):
		amalgamation = ""
		
		print("Config:")
		print(" target        = {0}".format(self.target))
		print(" working_dir   = {0}".format(os.getcwd()))
		print(" include_paths = {0}".format(self.include_paths))
		print("Creating amalgamation:")
		for file_path in self.sources:
			print(" - processing \"{0}\"".format(file_path))
			# Do not check the include paths while processing the source
			# list, all given source paths must be correct.
			if not Amalgamation.file_path(file_path, []):
				raise IOError("File not found: \"{0}\"".format(file_path))
			tunit = TranslationUnit(file_path, self.include_paths,
				self.included_files)
			amalgamation += tunit.content
		
		with open(self.target, 'w') as f:
			f.write(amalgamation)
		
		print("...done!\n")
		print("Files processed: {0}".format(self.sources))
		print("Files included: {0}".format(self.included_files))
		print("")

class TranslationUnit(object):
	
	def _include_files(self, included_files):
		# Find contexts in the content in which a found include
		# directive should be ignored.
		skippable_matches = []
		for pattern in self.skippable_patterns:
			skippable_match = pattern.search(self.content)
			while skippable_match:
				skippable_matches.append(skippable_match)
				skippable_match = pattern.search(self.content,
					skippable_match.end())
		
		# Search for include directives in the content, collect those
		# which should be included into the content.
		includes = []
		include_match = self.include_pattern.search(self.content)
		while include_match:
			should_include = True
			for skippable in skippable_matches:
				if include_match.start() > skippable.start() and \
						include_match.end() < skippable.end():
					should_include = False
					break
			include_path = include_match.group("path")
			actual_path = Amalgamation.file_path(include_path,
				self.include_paths)
			if should_include and actual_path:
				includes.append((include_match, actual_path))
			
			include_match = self.include_pattern.search(self.content,
				include_match.end())
		
		# Handle all collected include directives.
		prev_end = 0
		tmp_content = ''
		for include in includes:
			include_match, actual_path = include
			tmp_content += self.content[prev_end:include_match.start()]
			tmp_content += "// {0}\n".format(include_match.group(0))
			if not actual_path in included_files:
				tunit = TranslationUnit(actual_path, self.include_paths,
					included_files)
				tmp_content += tunit.content
			prev_end = include_match.end()
		tmp_content += self.content[prev_end:]
		self.content = tmp_content
		
		return len(includes)
	
	def __init__(self, file_path, include_paths, included_files):
		self.file_path = file_path
		self.include_paths = include_paths
		
		included_files.append(self.file_path)
		
		with open(self.file_path, 'r') as f:
			self.content = f.read()
			
			self.skippable_patterns = [
				re.compile(r'".*?(?<=[^\\])"'), # "complex \"string\" value"
				re.compile(r"//.*?\n"),         # // comment
				re.compile(r"/\*.*?\*/", re.S)  # /* comment */
			]
			
			# Handle simple include directives. Support for advanced
			# directives where macros and defines needs to expanded is
			# not a concern right now.
			self.include_pattern = re.compile(
				r'#\s*include\s*(<|")(?P<path>.*?)("|>)', re.S)
			
			self._include_files(included_files)

def main():
	argsparser = argparse.ArgumentParser(
		description="Amalgamate C source and header files.",
		usage="amalgamate.py -c path/to/config.json")
	argsparser.add_argument('-c', '--config', dest='config', required=True,
		metavar="", help="path to a JSON config file")
	
	amalgamation = Amalgamation(argsparser.parse_args())
	amalgamation.generate()

if __name__ == '__main__':
	main()

