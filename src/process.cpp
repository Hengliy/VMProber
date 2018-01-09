
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <inttypes.h>

#include <libvmi/libvmi.h>

#include "process.h"

addr_t proc[2000];
int proc_count = 0;
unsigned long tasks_offset = 0, pid_offset = 0, name_offset = 0 , pNodeOffset = 0;
unsigned long children_offset = 0, sibling_offset = 0;
unsigned long prev_offset = 0, next_offset = 0;

//获得结构体首地址函数
addr_t getStructAddr(addr_t address,unsigned long offset){
	return address - offset;
}

//获取节点信息函数
void getInfo(vmi_instance_t vmi,addr_t current_process,struct info *proc_info,int *sum){
		addr_t pNode = 0;
		vmi_pid_t pid = 0;
		vmi_pid_t ppid = 0;
		char *pname = NULL;
		addr_t pStart = 0;
		vmi_read_32_va(vmi, current_process + pid_offset, 0, (uint32_t*)&pid);
		char *procname = vmi_read_str_va(vmi, current_process + name_offset, 0);
		vmi_read_addr_va(vmi, current_process + pNodeOffset, 0, &pNode);
		pStart = pNode; //- tasks_offset
		vmi_read_32_va(vmi, pStart + pid_offset, 0, (uint32_t*)&ppid);
		pname = vmi_read_str_va(vmi, pStart + name_offset, 0);	
		proc_info[*sum].pid = pid;
		proc_info[*sum].name = procname;
		proc_info[*sum].addr = current_process;
		proc_info[*sum].ppid = ppid;
		proc_info[*sum].pname = pname;
		(*sum)++;
}

//找到节点的所有孩子节点函数
void findAllChildren(vmi_instance_t vmi,addr_t curProc,struct info *proc_info,int *sum){
	addr_t cNext = 0;
	addr_t cPrev = 0;
	vmi_read_addr_va(vmi, curProc + children_offset + next_offset, 0, &cNext);
	vmi_read_addr_va(vmi, curProc + children_offset + prev_offset, 0, &cPrev);
	if(cNext == curProc + children_offset){
		return;
	}
	addr_t fc = getStructAddr(cNext,sibling_offset);// 第一个子进程的进程初始地址
	proc[proc_count]= fc;					
	proc_count ++;
	getInfo(vmi,fc,proc_info,sum);
	addr_t pNext =cNext;
	while(pNext!= cPrev){
		addr_t fc_next = 0;
		vmi_read_addr_va(vmi, pNext + next_offset, 0, &fc_next);
		addr_t fc_bro = getStructAddr(fc_next,sibling_offset);		
		proc[proc_count]= fc_bro;					
		proc_count ++;
		getInfo(vmi,fc_bro,proc_info,sum);
		pNext = fc_next;	
	}						
}

//打印输出函数
void printInfo(vmi_instance_t vmi,struct info *proc,int *count){
	for(int i=0;i<(*count);i++)
	printf("[%5d] %s(struct addr:%"PRIx64") parent[%4d] %s\n", proc[i].pid, proc[i].name, proc[i].addr, proc[i].ppid, proc[i].pname);
}

//通过读取tree-offset.txt文件获取树遍历时所需的偏移量
unsigned long get_offset(char *name){
    FILE *file = fopen("tree-offset.txt", "r");
    if (file == NULL) {
        printf("file open error\n");
        return -1;
    }
    char line[256]; //存每行
    char str[40]; //偏移名
    char s[2];  //‘=’
    char value[20]; //偏移量
    unsigned long result; 
 while (fgets(line, sizeof(line), file)) { //fgets逐行读取文件至文件尾终止while循环
        sscanf(line, "%s %s %s", str,s,value); //sscanf解析每行数据
        result = atof(value); //将偏移量转化为unsigned类型
	if(strcmp(str,name) == 0){
        	break;
	}
 }
    fclose(file);
    return result;
}
//获取系统中的偏移量
void get_ostype(vmi_instance_t vmi){
	if (VMI_OS_LINUX == vmi_get_ostype(vmi)) {
        vmi_get_offset(vmi, "linux_tasks", &tasks_offset);
        vmi_get_offset(vmi, "linux_name", &name_offset);
        vmi_get_offset(vmi, "linux_pid", &pid_offset);
	pNodeOffset = get_offset("pNodeOffset");
	children_offset = get_offset("children_offset");
	sibling_offset = get_offset("sibling_offset");
	prev_offset = get_offset("prev_offset");
	next_offset = get_offset("next_offset");
    }
    else if (VMI_OS_WINDOWS == vmi_get_ostype(vmi)) {
        vmi_get_offset(vmi, "win_tasks", &tasks_offset);
        vmi_get_offset(vmi, "win_pname", &name_offset);
        vmi_get_offset(vmi, "win_pid", &pid_offset);
    }

    if (0 == tasks_offset) {
        printf("Failed to find win_tasks\n");
  //      goto error_exit;
    }
    if (0 == pid_offset) {
        printf("Failed to find win_pid\n");
 //       goto error_exit;
    }
    if (0 == name_offset) {
        printf("Failed to find win_pname\n");
 //       goto error_exit;
    }

    if (vmi_pause_vm(vmi) != VMI_SUCCESS) {
        printf("Failed to pause VM\n");
     //   goto error_exit;
    } // if
}

//获取系统中模块链表头节点
addr_t get_modulelist(vmi_instance_t vmi,addr_t next_module){
	vmi_pause_vm(vmi);
	switch(vmi_get_ostype(vmi))
    {
    case VMI_OS_LINUX:
        vmi_read_addr_ksym(vmi, "modules", &next_module);
        break;
    case VMI_OS_WINDOWS:
        vmi_read_addr_ksym(vmi, "PsLoadedModuleList", &next_module);
        break;
   // default:
   //     goto error_exit;
    }
	return next_module;
}

//获取系统中进程链表头节点
addr_t get_listhead(vmi_instance_t vmi,addr_t list_head){
    char *name2 = vmi_get_name(vmi);
    vmi_mode_t mode;

    if (VMI_FAILURE == vmi_get_access_mode(vmi, NULL, 0, NULL, &mode)){
   //     goto error_exit;
	}
    if ( VMI_FILE != mode ) {
        uint64_t id = vmi_get_vmid(vmi);
        printf("Process listing for VM %s (id=%"PRIu64")\n", name2, id);
    }
    else {
        printf("Process listing for file %s\n", name2);
    }
    free(name2);

    os_t os = vmi_get_ostype(vmi);

    if (VMI_OS_LINUX == os) {
     //   if ( VMI_FAILURE == vmi_translate_ksym2v(vmi, "init_task", &list_head) )
    //        goto error_exit;
	vmi_translate_ksym2v(vmi, "init_task", &list_head);
	list_head+=tasks_offset;
    }
    else if (VMI_OS_WINDOWS == os) {

     // find PEPROCESS PsInitialSystemProcess
    if(VMI_FAILURE == vmi_read_addr_ksym(vmi, "PsActiveProcessHead", &list_head)) {
        printf("Failed to find PsActiveProcessHead\n");
   //     goto error_exit;
        }
    }
	return list_head;
}
//获取树结构进程函数，存储到struct结构中，返回值为进程个数
int process_tree(vmi_instance_t vmi,struct info *proc_tree){
        addr_t list_head = 0, cur_list_entry = 0, next_list_entry = 0;
        addr_t current_process = 0;
        char *procname = NULL;
        vmi_pid_t pid = 0;
	int num_proc = 0;
        status_t status;
        get_ostype(vmi);

        list_head = get_listhead(vmi,list_head);
 
        cur_list_entry = list_head;
        if (VMI_FAILURE == vmi_read_addr_va(vmi, cur_list_entry, 0, &next_list_entry)) {
            printf("Failed to read next pointer in loop at %"PRIx64"\n", cur_list_entry);
    //      goto error_exit;
        }

        current_process = cur_list_entry - tasks_offset;
        vmi_read_32_va(vmi, current_process + pid_offset, 0, (uint32_t*)&pid);

        procname = vmi_read_str_va(vmi, current_process + name_offset, 0);
		
	//+++
	addr_t pNode = 0;
	vmi_pid_t ppid = 0;
	char *pname = NULL;
	addr_t pStart = 0;	
		
        if (!procname) {
            printf("Failed to find procname\n");
    //        goto error_exit;
        }

	getInfo(vmi,current_process,proc_tree,&num_proc);
        
	proc[proc_count] =  current_process;					
	proc_count ++;
	findAllChildren(vmi,current_process,proc_tree,&num_proc);
		
	if (procname) {
            free(procname);
            procname = NULL;
        }
		
	int p = 1;
	while(p<proc_count){
		findAllChildren(vmi,proc[p],proc_tree,&num_proc);
		p++;
	}
	return num_proc;
}

//获取链表结构进程函数，存储到struct结构中，返回获取进程的个数
int process_list(vmi_instance_t vmi,struct info *proc_list){
    addr_t list_head = 0, cur_list_entry = 0, next_list_entry = 0;
    addr_t current_process = 0;
    char *procname = NULL;
    vmi_pid_t pid = 0;
    int num_proc = 0;
    status_t status;
    os_t os = vmi_get_ostype(vmi);
    get_ostype(vmi);

    list_head = get_listhead(vmi,list_head);
    cur_list_entry = list_head;
    if (VMI_FAILURE == vmi_read_addr_va(vmi, cur_list_entry, 0, &next_list_entry)) {
        printf("Failed to read next pointer in loop at %"PRIx64"\n", cur_list_entry);
    //    goto error_exit;
    }

    while (1) {
        current_process = cur_list_entry - tasks_offset;
        vmi_read_32_va(vmi, current_process + pid_offset, 0, (uint32_t*)&pid);
        procname = vmi_read_str_va(vmi, current_process + name_offset, 0);

        if (!procname) {
            printf("Failed to find procname\n");
      //      goto error_exit;
        }
	getInfo(vmi,current_process,proc_list,&num_proc);
        if (procname) {
            free(procname);
            procname = NULL;
        }

        /* follow the next pointer */
        cur_list_entry = next_list_entry;
        status = vmi_read_addr_va(vmi, cur_list_entry, 0, &next_list_entry);
        if (status == VMI_FAILURE) {
        //    printf("Failed to read next pointer in loop at %"PRIx64"\n", cur_list_entry);
        //    goto error_exit;
        }

        if (VMI_OS_WINDOWS == os && next_list_entry == list_head) {
            break;
        }
        else if (VMI_OS_LINUX == os && cur_list_entry == list_head) {
            break;
        }

    };
	return num_proc;
}

//获取模块结构名函数，存储到struct的name中，并返回模块个数
int get_module(vmi_instance_t vmi,struct info *module_info){
    int sum = 0;
    addr_t next_module = 0, list_head = 0;
    list_head = get_modulelist(vmi,next_module);
    next_module = list_head;
    /* walk the module list */
    while (1) {
        addr_t tmp_next = 0;
        vmi_read_addr_va(vmi, next_module, 0, &tmp_next);
        /* if we are back at the list head, we are done */
        if (list_head == tmp_next) {
            break;
        }
        if (VMI_OS_LINUX == vmi_get_ostype(vmi)) {
            char *modname = NULL;
            if (VMI_PM_IA32E == vmi_get_page_mode(vmi, 0)) {  
                modname = vmi_read_str_va(vmi, next_module + 16, 0);
            }
            else {
                modname = vmi_read_str_va(vmi, next_module + 8, 0);
            }
	    module_info[sum].name = modname;
	    (sum)++;
      //    free(modname);
        }
        else if (VMI_OS_WINDOWS == vmi_get_ostype(vmi)) {
            unicode_string_t *us = NULL;
            if (VMI_PM_IA32E == vmi_get_page_mode(vmi, 0)) {
                us = vmi_read_unicode_str_va(vmi, next_module + 0x58, 0);
            } else {
                us = vmi_read_unicode_str_va(vmi, next_module + 0x2c, 0);
            }
            unicode_string_t out = { 0 };
            if (us &&
                VMI_SUCCESS == vmi_convert_str_encoding(us, &out,
                                                        "UTF-8")) {
                printf("%s\n", out.contents);
                free(out.contents);
            }   // if
            if (us)
                vmi_free_unicode_str(us);
        }
        next_module = tmp_next;
    }
	return sum;
}

//模块结构输出函数
void module_list(vmi_instance_t vmi,struct info *module){
	int module_sum = 0;
	module_sum = get_module(vmi,module);
	for(int i=0;i<module_sum;i++){
		printf("%s\n",module[i].name);
	}
}

char * left(char *dst,char *src, int n)  
{  
    char *p = src;  
    char *q = dst;  
    int len = strlen(src);  
    if(n>len) n = len;  
    while(n--) *(q++) = *(p++);  
    *(q++)='\0';  
    return dst;  
} 

//通过配置文件libvmi.conf获取虚拟机名称，存储到数组name中并返回虚拟机个数
int get_VMname(char **name){
    FILE *file = fopen("libvmi.conf", "r");
    if (file == NULL) {
        printf("file open error\n");
        return -1;
    }
    int sum = 0;
    char line[1024];     
    while (fgets(line, sizeof(line), file)) { 
	char *str = NULL;         
	int count = 0;
	char *p = line;
	char *a = NULL;
        while(*p != '\0'){
	    if(*p != ' '){
	        count++;
	    }
	    if(*p == '{'){
		count--;
		str = (char*)malloc(sizeof(char)*count);
		name[sum]  = left(str,line,count);
		sum++;
	    }
	    p++;
	}//每行while
 }
    fclose(file);
    return sum;
}

char* copy(char* from,char *to) {
	char* p = from;
	int len = strlen(p);
	to = (char *)malloc(sizeof(char)*len);
	char* d = to;
	while (*p != '\n') {
		*d = *p;
		p++;
		d++;
	}
	*d = '\0';
	return to;
}

//通过指令获取正在运行的虚拟机状态以及信息并保持到文件xl_info,读取文件保存到数组并返回读取行数值
int get_xl(char **a) {
	system("sudo rm xl_info");
	system("sudo xl list >>xl_info");
	FILE *file = fopen("xl_info", "r");
	if (file == NULL) {
		printf("file open error");
		return -1;
	}
	int sum = 0;
	char data[1024];
	while(fgets(data,sizeof(data),file)){
		a[sum]=copy(data, a[sum]);
//		printf("%s\n", a[sum]);
		sum++;
	}
	fclose(file);
//	printf("\n行数：%d\n", sum);
	return sum;
}

