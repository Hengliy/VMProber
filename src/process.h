
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <inttypes.h>

#include <libvmi/libvmi.h>

#include<time.h>

//��Ž��̽ڵ���Ϣ
struct info{
	vmi_pid_t pid; //�ڵ�
	char *name;
	addr_t addr;
	vmi_pid_t ppid; //���ڵ�
	char *pname;
	addr_t paddr;
};
//��ýṹ���׵�ַ����
addr_t getStructAddr(addr_t address,unsigned long offset);
//��ȡ�ڵ���Ϣ����
void getInfo(vmi_instance_t vmi,addr_t current_process,struct info *proc_info,int *sum);
//�ҵ��ڵ�����к��ӽڵ㺯��
void findAllChildren(vmi_instance_t vmi,addr_t curProc,struct info *proc_info,int *sum);
//��ӡ�������
void printInfo(vmi_instance_t vmi,struct info *proc,int *count);

//��ȡ������ʱ�����ƫ����
unsigned long get_offset(char *name);
//��ȡϵͳ�е�ƫ����
void get_ostype(vmi_instance_t vmi);
//��ȡϵͳ��ģ������ͷ�ڵ�
addr_t get_modulelist(vmi_instance_t vmi,addr_t next_module);

//��ȡϵͳ�н�������ͷ�ڵ�
addr_t get_listhead(vmi_instance_t vmi,addr_t list_head);
//��ȡ���ṹ���̺������洢��struct�ṹ�У�����ֵΪ���̸���
int process_tree(vmi_instance_t vmi,struct info *proc_tree);
//��ȡ����ṹ���̺������洢��struct�ṹ�У����ػ�ȡ���̵ĸ���
int process_list(vmi_instance_t vmi,struct info *proc_list);
//��ȡģ��ṹ���������洢��struct��name�У�������ģ�����
int get_module(vmi_instance_t vmi,struct info *module_info);
//ģ��ṹ�������
void module_list(vmi_instance_t vmi,struct info *module);
//��ȡ�ַ���
char * left(char *dst,char *src, int n);
//ͨ�������ļ�libvmi.conf��ȡ��������ƣ��洢������name�в��������������
int get_VMname(char **name);

char* copy(char* from,char *to);
//ͨ��ָ���ȡ�������е������״̬�Լ���Ϣ�����ֵ��ļ�xl_info,��ȡ�ļ����浽���鲢���ض�ȡ����ֵ
int get_xl(char **a);

