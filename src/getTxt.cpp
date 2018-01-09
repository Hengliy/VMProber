#include <bits/stdc++.h>
using namespace std;

FILE * getTxt(char* cmda, char * dir) {
    // char  all[100] = "sshpass -p 1 ssh ybhy@192.168.122.2 ls -i";
    // all = " ";
    system("echo is linking¡«");
    char all[100];

    for (int i = 0; i < 100 ; i++) {
        all[i] = ' ';
    }
    all[0] = '\0';
    int sta;

	printf("%s\n",cmda);

    string cmd = cmda;

    if (cmd == "xl") {
        char *s = "sudo xl list > xl.txt";
        strcat(all, s);
        // return popen("echo \"1\" | sudo -S xl list > xl.txt ", "w");
    }else {
        if (cmd == "ls") {
            char *s  = "sshpass -p ybhy123 ssh ybhy@192.168.122.233 ls -i ";
            strcat(all, s);
            strcat(all, "/");
            strcat(all, dir);
            char *p = " > ls.txt";
            strcat (all, p);
        } else if (cmd == "ps") {

            char *s  = "sshpass -p ybhy123 ssh ybhy@192.168.122.233 ps -A ";
            strcat(all, s);
            // strcat(all, "/");
            // strcat(all, dir);
            char *p = "> ps.txt";
            strcat (all, p);
        }else if (cmd == "tree") {
            char *s  = "sshpass -p ybhy123 ssh ybhy@192.168.122.233 tree -i ";
            strcat(all, s);
            strcat(all, "/");
            strcat(all, dir);
            char *p = " > tree.txt";
            strcat (all, p);            
        } else {
	
		char *s  = "sshpass -p ybhy123 ssh ybhy@192.168.122.233 ps -A ";
          //  char *s  = "sshpass -p ybhy123 ssh ybhy@192.168.122.233 lsmod ";
            strcat(all, s);
            // strcat(all, "/");
            // strcat(all, dir);
		char *p = "> ps.txt";
         //   char *p = "> lsmod.txt";
            strcat (all, p);
        }

        // printf("%s\n", all);
        
    }
    std::cout<< all<< "\n";

    return popen(all, "w");     
}
