#include <iostream>
#include <chrono>
#include <queue>

using namespace std;

#include "mproto.h"

queue<uint8_t> serial1;

void serial1_put_byte(uint8_t byte)
{
    serial1.push(byte);
}

int16_t serial1_get_byte()
{
    if ( serial1.empty() )
        return -1;

    int16_t res = serial1.front();
    serial1.pop();

    return res;
}

mptime_t get_time()
{
    chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds >(
        chrono::system_clock::now().time_since_epoch()
    );

    return ms.count() % 100000000;
}

void cb(mpcmd_t cmd, uint8_t *data, size_t len)
{
    cout << "Received data on command " << to_string(cmd) << " / " << to_string(*((uint32_t*)data)) << endl;
}


int main (int argc, char **argv)
{
    mproto_func_ctx_t s1_funcs;
    s1_funcs.get_byte = serial1_get_byte;
    s1_funcs.put_byte = serial1_put_byte;
    s1_funcs.get_time = get_time;

    mproto_ctx_t mproto_s1 = mproto_init(&s1_funcs);

    for ( size_t i = 0; i < 10; i++ ) {
        mproto_register_command(mproto_s1, i, cb);
    }

    for ( size_t i = 0; i < 10; i++ ) {
        uint32_t data = i + 20;
        mproto_send_data(mproto_s1, i, (uint8_t*)(&data), sizeof(data));
        cout << "Send uint32 for cmd: " << i << " with value: " << data << endl;
    }

    /* 1 sec spin */
    cout << mproto_spin(mproto_s1, 1000) << endl;

    return EXIT_SUCCESS;
}
