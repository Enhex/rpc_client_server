#include "RPC.h"
#include "shared.h"
#include <hla/object.h>
#include <hla/utility.h>
#include <iostream>
#include <thread>

void f(asio::ip::tcp::socket& socket)
{
	auto x = read_bytes<int>(socket);
	std::cout << "f(" << x << ")\n";
}

int main()
{
	using asio::ip::tcp;

	asio::io_context context;

	RPC<RPC_ID> rpc(context, rpc_port);
	rpc.accept();

	// register RPC
	rpc.functions[f_id] = f;

	auto threads = hla::thread_pool_run(context);

	hla::join_threads(threads);
}