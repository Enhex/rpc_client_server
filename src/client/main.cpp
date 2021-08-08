#include "shared.h"
#include <RPC.h>
#include <hla/object.h>
#include <hla/utility.h>
#include <thread>
#include <iostream>

int main(int argc, char *argv[])
{
	using asio::ip::tcp;

	if(argc != 2) {
		std::puts("usage: client [server IP]");
		return 0;
	}
	auto server_ip = argv[1];

	asio::io_context context;
	auto threads = hla::thread_pool_run(context);

	std::cout << "port " << rpc_port << std::endl;

	// call RPC via TCP
	tcp::socket rpc_client(context);
	hla::connect(rpc_client, server_ip, rpc_port);
	RPC_ID rpc_call_id = 1;

	write_bytes(rpc_client, rpc_call_id);
	write_bytes(rpc_client, 2);

	rpc_client.shutdown(rpc_client.shutdown_both);
	context.stop();
	hla::join_threads(threads);
}