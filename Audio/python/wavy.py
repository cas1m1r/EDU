import pyaudio
import wave
import sys
import os

class Wavy:
	CHUNK = 1024

	def __init__(self,filename):
		self.name = filename.split('/')[-1]
		self.wave_reader = wave.open(filename, 'rb')
		# check that compression type is none!
		compression = self.wave_reader.getcomptype() 
		if compression != 'NONE':
			print('[!!] %s compression is not supported' % compression)
		self.FrameRate = self.wave_reader.getframerate()
		self.n_channel = self.wave_reader.getnchannels()
		self.n_samples = self.wave_reader.getnframes()
		self.sample_sz = self.wave_reader.getsampwidth()

	def __str__(self):
		s = 'Filename:       %s\n' % self.name
		s += 'Frame Rate:    %d\n' % self.FrameRate
		s += 'N Channels:    %d\n' % self.n_channel
		s += 'N Samples:     %d\n' % self.n_samples
		s += 'Sample Size: 	 %d bytes'   % self.sample_sz
		return s

	def play(self):
		# create an audio object
		p = pyaudio.PyAudio()

		# open stream based on the wave object which has been input.
		stream = p.open(format = p.get_format_from_width(self.sample_sz),
		                channels = self.n_channel,
		                rate = self.FrameRate,
		                output = True)
		print('\033[1m\033[32m** Playing Song **\033[0m')
		print(str(self))
		# read data (based on the chunk size)
		data = self.wave_reader.readframes(self.CHUNK)
		# play stream (looping from beginning of file to the end)
		while data != '':
		    # writing to the stream is what *actually* plays the sound.
		    stream.write(data)
		    data = self.wave_reader.readframes(self.CHUNK)

		# cleanup stuff.
		stream.close()    
		p.terminate()


def main():
	if len(sys.argv) < 2:
	    print("Plays a wave file.\n\nUsage: %s filename.wav" % sys.argv[0])
	    sys.exit(-1)
	if not os.path.isfile(sys.argv[1]):
		print('[!] Cannot find %s' % sys.argv[1])
	# Open wave File 
	song = Wavy(sys.argv[1])
	song.play()

if __name__ == '__main__':
	main()
