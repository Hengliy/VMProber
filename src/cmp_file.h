// #ifndef CMP_FILE_H
// #define CMP_FILE_H

// #define NAME_SIZE 100

// #include "definition.h"
// #include <libvmi/libvmi.h>
// #include <stdlib.h>
// #include <string.h>
// #include <errno.h>
// #include <sys/mman.h>
// #include <cstdio>
// #include <algorithm>
// #include <string>
// #include <vector>
// #include <time.h>
// #include <iostream>
// using namespace std;


// /*�õ���Ŀ¼��dentry��ַ*/
// bool get_root_dentry(VM_vmi& vmi_os);

// /*������ַ������·��vector*/
// vector<string> get_path_arry(string path);

// /*�õ�Ŀ��Ŀ¼��Ŀ¼���ַ*/
// addr_t get_search_dentry(VM_vmi& vmi_os,string path);

// bool get_file_info(VM_file& newnode);

// /*ls����*/
// bool do_ls(VM_vmi& vmi_os,addr_t ls_addr);

// /*�ļ���ӡ������*/
// //bool cmp_file(VM_vmi& vmi_os,char* path);

// /*����ls����*/
// //bool walk_flist(const VM_vmi& vmi_os);

// /*�ڱ������ָ��Ŀ¼*/
// addr_t find_dentry_addr(const VM_vmi& vmi_os,addr_t parent_dentry_addr,string dentry_name);

// //bool walk_flist(const VM_vmi& vmi_os);

// //vector<VM_file*> cmp_ls(const VM_vmi& vmi_os,char* path);

// void do_dfs(VM_vmi& vmi_os,addr_t subdirs_head,VM_file* parentNode,int deep,vector<string>& file_vector);

// void init_file_tree(VM_vmi& vmi_os,string path);

// //void print_LRU_list(VM_vmi& vmi_os,addr_t dentry_addr);

// FILE * getTxt(char* cmd, char * dir);

// void cmp_file(VM_vmi& vmi_os,char* path);

// void traverse_file_tree(VM_file* fileNode,int deep);

// void dfs_cmp_file(VM_file* fileNode,int deep,vector<string>& file_vector);


// #endif // WXTESTMAIN_H
