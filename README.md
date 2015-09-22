# moulinette-client
This program is the client of a moulinette for EPITECH students. It will connect to the moulinette server, which will clone the git repository for a project and perform some tests on it. This should help them track and patch their errors.

## Compiling the client
Run:

    git clone https://github.com/Ethiraric/moulinette-client.git
    cd moulinette-client
    make

The executable is named 'mouli'.

## The key file
The key file contains the key AES will use to encrypt the password. It is personal and must not be shared. The server must have the same key attached to your login. It is an hexadecimal string of 64 digits

## The config file
You must indicate on what host and port the moulinette client should connect. For example:

    host=example.org
    port=1234

is a valid config file.

## Running your tests
You should call mouli the following way:

    ./mouli <path-to-config> <path-to-key>

replacing `<path-to-key>` with the actual path to your key file, and `<path-to-config>` with the actual path to your config file.

You will be prompted your login and UNIX password, and then the repository you want to be tested.

The server will clone/pull your repository, perform the test and the output will be displayed on the standard output.