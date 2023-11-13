from ctypes import *
import random
import string
import sys
import os

letters = list(string.lowercase) + list(string.uppercase)

def swap(filename,destroy):
	out = []
	for ln in open(filename,'r').readlines():
		out.append(line.replace('\n', ''))
	if destroy:
		os.remove(filename)
	return filename

def create_random_filename(ext):
	return '%s%s' % (''.join(random.sample(letters, 6)), ext)


def cexec(cmd, show):
	tmp = create_random_filename('.txt')
	os.system('%s >> %s' % (cmd, tmp))
	result = open(tmp,'r').read()
	if show:
		print(tmp)
	os.remove(tmp)
	return result

def usage():
	# May wany to add to this
	print('Usage: python snoo,py [PID]')
	exit()

def isaproc(pid):
	isProc = False
	if str(pid) in os.listdir('/proc'):
		isProc = True
	return isProc

def read_maps(pid):
	# Need to be root for this
	results = {}
	for line in open('/proc/%d/maps' % pid,'r').readlines():
		raw_data = line.split(' ')
		offsets = raw_data[0].split('-')
		resource = line.split(' ')[-1].replace('\n', '')
		print(resource)

def main():
	# check args 
	if len(sys.argv) <= 1:
		usage()
	if '-p' in sys.argv:
		PID = int(''.join(sys.argv)[''.join(sys.argv).find('-p')+2:])
	
		# check for pid 
		if not isaproc(PID):
			print('[!!] Cant find PID: %d' % PID)
		else:
			read_maps(PID)

if __name__ == '__main__':
	main()