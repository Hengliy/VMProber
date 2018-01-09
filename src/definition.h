#ifndef _DEFINITION_H
#define _DEFINITION_H

#include <libvmi/libvmi.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <inttypes.h>
#include <capstone/capstone.h>
#include "Features.h"

using namespace std;

struct VM_list_vm
{
	string name;
	int id,mem,cpu,num;
	double time;
	string stat;
};

struct VM_list_head
{
	struct VM_list_head *next;
	struct VM_list_head *pre;
};

struct VM_process
{
	int state;//״̬
	unsigned int pid;//pid
	char *comm=NULL;//��������
	uint8_t code[3000];
	uint8_t date[1000];
	uint8_t stack[1000];
	int code_long ;
	int date_long ;
	int stack_long ;	
	uint64_t start_time ;			
	unsigned int flag;																																																									
	unsigned int parent_pid;
	unsigned int sibling_pid;
	int prio;
	int static_prio;
	int normal_prio;
	int rt_priority;
	unsigned long start_code_address;
	unsigned long end_code_address;
	unsigned long start_date_address;
	unsigned long end_date_address;
	unsigned long start_stack_address;
	unsigned long end_stack_address;

	csh handle;
  	cs_insn *insn;
	size_t asm_count;
	/*����ά��������ʽ�ṹ*/
	struct VM_list_head tasks;
	/*����ά���������νṹ*/
	struct VM_list_head parent;
	struct VM_list_head children;
	struct VM_list_head sibling;
};

struct VM_module
{
	int state;
	char *name;
	unsigned long used_by_number;

	char *version;
	char *srcversion;
	char *args;
	unsigned int size;
	unsigned int text_size;
	unsigned long init_code_address;
	uint8_t code[1000];

	vector<string> used_by_name;

	unsigned int num_syms;
	struct VM_list_head list;
	 MalSoftware* rootkid; 

	csh handle;
  	cs_insn *insn;
	size_t asm_count;

};

struct VM_file
{
	string name;               //Ŀ¼������
	unsigned long id;          //inode��id
    unsigned long state;       //״̬
	unsigned int user_id;      //ʹ����id
    unsigned short bytes;      //��������ռ�ֽ���
	unsigned short mode;       //Ȩ��
	string mtime;              //���һ���޸ĵ�ʱ��

	unsigned int  i_gid;       //�û���
	unsigned int i_flags;      //�ļ�ϵͳ��־
	string s_type;             //�ļ�ϵͳ����
	unsigned int i_rdev;       //�豸���
	unsigned int i_version;    //�汾��
	unsigned i_count;     	   //���ü���
	string parent_name;        //��Ŀ¼����
	bool isfile;			   //�ļ�����Ŀ¼

	bool ishidden;             //�ǲ��������ļ�
	VM_list_head bro;		   //ָ���ֵ�����
	VM_list_head subdirs;	   //ָ��������
	


};

struct VM_vmi{
	vmi_instance_t vmi;
	unsigned char *memory ;
    uint32_t offset;
    addr_t list_head , current_list_entry, next_list_entry ,next_module,head_module;
    addr_t current_process,head_process;
    addr_t tmp_next ;
    char *procname ;
    uint32_t pid ,state,flag,prio,static_prio,normal_prio,rt_priority;
    uint64_t start_code,end_code,start_date,end_date,start_stack,end_stack,mm;
    unsigned long tasks_offset, pid_offset, name_offset,children_offset,sibling_offset,state_offset;
    unsigned long flag_offset,prio_offset,static_prio_offset,normal_prio_offset,rt_priority_offset;
    unsigned long start_code_offset,end_code_offset,start_date_offset,end_date_offset,start_stack_offset,end_stack_offset,mm_offset;
    unsigned long root_dentry_addr;

	unsigned long module_state_offset,module_name_offset,module_version_offset,module_srcversion_offset,module_num_syms_offset;
    unsigned long module_list_offset;
   
    unsigned int num1_pid[500],num2_pid[500],process_number1,process_number2;
    unsigned int hide_process_pid[500],hide_process_number;//hide_process_pid[]�������ؽ���pid

    /*******file_offset***********/
  	unsigned long fs_task_offset;
	unsigned long dentry_root_fs_offset;
	unsigned long d_parent_dentry_offset;
	unsigned long d_child_dentry_offset;
	unsigned long d_subdirs_dentry_offset;
	unsigned long name_dentry_offset;    
	unsigned long d_inode_dentry_offset;
	unsigned long d_sb_dentry_offset;

	unsigned long imode_inode_offset;
	unsigned long i_uid_inode_offset;
	unsigned long i_bytes_inode_offset;
	unsigned long i_state_inode_offset;
	unsigned long i_atime_sec_inode_offset;
	unsigned long i_ino_inode_offset;

	///////////////////////////////////////
	unsigned long i_gid_inode_offset;
	unsigned long i_flags_inode_offset;
	unsigned long i_rdev_inode_offset;
	unsigned long i_version_inode_offset;
	unsigned long i_count_inode_offset;
	unsigned long i_sb_inode_offset;
	unsigned long s_type_superblock_offset;
	unsigned long name_s_type_offset;

	status_t status;

    struct VM_process process;
    struct VM_module module;
	struct VM_file file_list_head;
	struct VM_file file_root;
	map <int, VM_process*> pid_to_process;
	vector<VM_file> hidden_file;
};



 //���ݽṹ�ĳ�Ա�������Ӧ�ṹ��ַ
#define VM_list_entry(ptr, type, member) ({      \
 const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
  (type *)( (char *)__mptr - offsetof(type,member) );})

#define VM_offsetof(TYPE, MEMBER)  ((size_t)&((TYPE *)0)->MEMBER)

#define VM_list_for_each(pos, head) \
        for (pos = (head)->next; pos != (head); pos = pos->next)

#define process_tree_no_pid 9999;//����������ʾ

#endif
