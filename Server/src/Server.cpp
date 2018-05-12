#include "includes/lobby.h"
#include <iostream>
#include <random>
#include <ctime>
#include <vector>
//#include "includes/library.h"
using namespace std;


void init(string library_f = "library", string nature_f = "nature") {
    srand(time(0));
    //library_gen(library_f, 10);
    //library_fill(library_f);
    //nature_gen(nature_f, 20);
    //nature_fill(nature_f);
}


int main() {
    init();
    lobby game;
    while (true) {
        if (game.num_of_players() > 1) {
            int cli = 0;
            for (auto el : game.get_players()) {
                cout << el.first << " ";
            }
            cout << endl;

            string str;
            cin >> cli;
            cin.ignore();
            getline(cin, str);
            /*game.recv_from(cli);
            game.players[cli].in.print();
            str = "HTTP/1.x 200 OK\nDate: Tue, 21 Jul 2009 17:09:54 GMT\nLast-Modified: Tue, 15 Nov 2005 13:24:10 GMT\nContent-Length: 89\nConnection: keep-alive\nContent-Type: text/html\n\n<HTML>\n<HEAD>\n<TITLE>Example Web Page</TITLE>\n</HEAD>\n<body>\n<p>HI!</p>\n</BODY>\n</HTML>\n\n";
            game.send_to(cli, str);
            game.recv_from(cli);
            game.players[cli].in.print();
            cin >> str;
            str = "HTTP/1.x 200 OK\nDate: Tue, 21 Jul 2009 17:09:54 GMT\nLast-Modified: Tue, 15 Nov 2005 13:24:10 GMT\nContent-Length: 92\nConnection: keep-alive\nContent-Type: text/html\n\n<HTML>\n<HEAD>\n<TITLE>Example Web Page</TITLE>\n</HEAD>\n<body>\n<p>HI!HI!</p>\n</BODY>\n</HTML>\n\n";
            */
            game.send_to(cli, str);
            if (str.size() > 0 && str[0] == '~') {
                if (str.size() > 1 && str[1] == '~') {
                    break;
                }
            }
        }
    }
    system("pause");
    return 0;
}