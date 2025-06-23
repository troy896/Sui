#include <selinux.h>
#include <logging.h>
#include <cstring>

bool check() {
    if (selinux_check_access("u:r:adbd:s0", "u:r:adbd:s0", "process", "setcurrent", nullptr) != 0) {
        PLOGE("u:r:adbd:s0 u:r:adbd:s0 process setcurrent not allowed");
        return false;
    }

    char *curr_con = nullptr;
    if (getcon(&curr_con) != 0) {
        PLOGE("getcon");
        return false;
    }

    if (selinux_check_access("u:r:adbd:s0", curr_con, "process", "dyntransition", nullptr) != 0) {
        PLOGE("u:r:adbd:s0 %s process dyntransition not allowed", curr_con);
        return false;
    }

    if (selinux_check_access("u:r:system_server:s0", curr_con, "unix_stream_socket", "getopt", nullptr) != 0) {
        PLOGE("u:r:system_server:s0 %s unix_stream_socket getopt not allowed", curr_con);
        return false;
    }

    if (selinux_check_access("u:r:system_server:s0", curr_con, "unix_stream_socket", "getattr", nullptr) != 0) {
        PLOGE("u:r:system_server:s0 %s unix_stream_socket getopt not allowed", curr_con);
        return false;
    }

    if (selinux_check_access("u:r:system_server:s0", curr_con, "unix_stream_socket", "read", nullptr) != 0) {
        PLOGE("u:r:system_server:s0 %s unix_stream_socket getopt not allowed", curr_con);
        return false;
    }

    if (selinux_check_access("u:r:system_server:s0", curr_con, "unix_stream_socket", "write", nullptr) != 0) {
        PLOGE("u:r:system_server:s0 %s unix_stream_socket getopt not allowed", curr_con);
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    return check() ? 0 : 1;
}