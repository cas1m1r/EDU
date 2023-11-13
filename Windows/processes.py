import json
import sys
import os


def run(cmd):
	result = ''
	try:
		c = os.popen(cmd)
		result = c.read()
		c.close()
	except os.error:
		pass
	return result


def non_empty(fields):
	subset = []
	for element in fields:
		if len(element) >= 1:
			subset.append(element)
	return subset

def get_pid_details(pid):
	details = {}
	for ln in run(f'wmic process where "ProcessID={pid}" get /format:list').split('\n'):
		elmt = ln.split('=')
		if len(elmt)>1:
			details[elmt[0]] = elmt[1]
	return details

def enumerate_process(exename):
	processes = {}
	for ln in run(f'tasklist /svc /fi "imagename eq {exename}"').split('\n')[3:]:
		fields = non_empty(ln.split(' '))
		# first will be process name and second will be PID
		if len(fields) > 2 and fields[1] not in processes.keys():
			details = get_pid_details(fields[1])
			processes[int(fields[1])] = details
	return processes


def main():
	if len(sys.argv) > 2 and '--enum' in sys.argv:
		exe = sys.argv[2]
		print(f'Enumerating PIDs and children processes of {exe}')
		logfile = f"{exe.split('.exe')[0]}.json"
		pids = enumerate_process(exe)
		open(logfile, 'w').write(json.dumps(pids, indent=2))
	else:
		example = enumerate_process('svchost.exe')
		open('svchost.json','w').write(json.dumps(example, indent=2))


if __name__ == '__main__':
	main()
