#ifndef _PROCESS_LIST_H
#define _PROCESS_LIST_H

#include "definition.h"
#include <algorithm>
#include <iostream>
using namespace std;

/*��ʼ�������vmi,
	(1):  argv->���������
	(2):  ���ݽṹVM_vmi
*/
int VM_vmi_init(char *argv,VM_vmi &vmi);
bool print_XL_list(); 
/*��ʼ��vmi�ĳ�Ա����process(����)
	(1):  VM_process->vmi��Ա����
*/
int VM_process_init(struct VM_process &process);
/*����vmi������Ľ�����������vmi��Ա����process��ʽ�ṹ
	(1):  Ҫ�����������
	(2):  ��������ĳ�Ա����process
*/
int VM_find_process_list(VM_vmi &vmi_os,VM_process &process);
/*VM_find_process_tree����->dfs����vmi������Ľ�����������vmi��Ա����process��ʽ�ṹ
	(1):  Ҫ�����������
	(2):  ��������ĳ�Ա����process
*/
void VM_find_process_tree_dfs(VM_vmi &vmi_os,VM_process &process,addr_t current_process,int b); // dfs��ӡ������
void VM_find_process_tree(VM_vmi &vmi_os,VM_process &process); // ����vmi����

void printf_process_tree(const VM_process &process,int b);//�ն˴�ӡ������

void get_module_infornmation(VM_vmi &vmi_os,addr_t current_module);
int VM_module_init(VM_module &module);//��ʼ��ģ��
void VM_find_modules_list( VM_vmi &vmi_os,VM_module &module);//����vmi�����ģ����������vmi��Ա����module��ʽ�ṹ
void VM_find_process_code(VM_vmi &vmi_os,VM_process &process);//���ҽ��̴����

int VM_find_process_hide(VM_vmi &vmi_os);

void VM_lsmod(VM_module& head);
bool walk_module(VM_vmi &vmi_os);//����ģ��
vector<VM_module*> cmp_lsmod(VM_vmi &vmi_os);
vector<VM_process*> cmp_process(VM_vmi &vmi_os);

/**/

/*������ַ������·��vector*/
vector<string> get_path_arry(string path);

/*�õ�Ŀ��Ŀ¼��Ŀ¼���ַ*/
addr_t get_search_dentry(VM_vmi& vmi_os,string path);

bool get_file_info(VM_file& newnode);

/*ls����*/
bool do_ls(VM_vmi& vmi_os,addr_t ls_addr);

/*�ڱ������ָ��Ŀ¼*/
addr_t find_dentry_addr(const VM_vmi& vmi_os,addr_t parent_dentry_addr,string dentry_name);

void do_dfs(VM_vmi& vmi_os,addr_t subdirs_head,VM_file* parentNode,int deep,vector<string>& file_vector);

void init_file_tree(VM_vmi& vmi_os,string path);


void traverse_file_tree(VM_file* fileNode,int deep);

vector<VM_file*> cmp_file(VM_vmi& vmi_os,char* path);

vector<VM_file*> dfs_cmp_file(VM_file* fileNode,int deep,vector<string>& file_vector);

vector<VM_module*> cmp_lsmod(VM_vmi &vmi_os);

bool walk_module(VM_vmi &vmi_os);

int VM_module_init(VM_module &module);

void VM_find_modules_list(VM_vmi &vmi_os,VM_module &module);

void get_module_info(VM_vmi &vmi_os,VM_module &module,addr_t current_module);

bool get_vm_list(VM_list_vm *v);

#endif
