build:
	/usr/bin/g++ -fdiagnostics-color=always -g ./PacketException/PacketException.cpp -g ./PacketReceiver/PacketReceiver.cpp -g ./PacketSender/PacketSender.cpp -g ./PacketQueue/PacketQueue.cpp -g ./PacketThread/*.cpp -g ./main.cpp -o ./radio-aggregator -lpthread
clean:
	rm -rf radio-aggregator main PacketThread/PacketThreadGroup PacketException/PacketException PacketSender/PacketSender PacketReceiver/PacketReceiver
