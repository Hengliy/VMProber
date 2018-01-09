#include "definition.h"
#include "getTxt.h"
#include <stdio.h>
#include <inttypes.h>
#include <capstone/capstone.h>
#include <iostream>
using namespace std;

                                           
int VM_process_init(struct VM_process &process)
{
	process.tasks.next = &process.tasks;
	process.tasks.pre = &process.tasks;

}

void VM_find_process_asm(VM_vmi &vmi_os,VM_process &process,addr_t start_offset)
{
	string asm_code;
	for (unsigned long i = process.start_code_address+start_offset; i < process.start_code_address+start_offset+300; i+=1){
		uint8_t temp=0;
		vmi_read_8_va(vmi_os.vmi, (addr_t)i, process.pid, &temp);
        process.code[process.code_long++] = temp;  
        //if(1000<process.code_long)
		asm_code+=temp; 
	}
    	if (cs_open(CS_ARCH_X86, CS_MODE_64, &process.handle) != CS_ERR_OK)
        return ;
    	process.asm_count = cs_disasm(process.handle, (uint8_t*)asm_code.c_str(), asm_code.size()-1, process.start_code_address+start_offset, 0, 			&process.insn);
}

void VM_find_process_code(VM_vmi &vmi_os,VM_process &process)
{//	printf("VM_find_process_code in\n");
	int k=0;
    //string asm_code;
	for (unsigned long i = process.start_code_address; i < process.end_code_address; i+=1){
        if(600<process.code_long||600<(i-process.start_code_address))
            break;
		uint8_t temp=0;
		vmi_read_8_va(vmi_os.vmi, (addr_t)i, process.pid, &temp);
        process.code[process.code_long++] = temp;  
        //if(1000<process.code_long)
	//	asm_code+=temp; 
	}

    VM_find_process_asm(vmi_os,process,0x3000);
 //
   // if (cs_open(CS_ARCH_X86, CS_MODE_64, &process.handle) != CS_ERR_OK)
   //     return ;
   // process.asm_count = cs_disasm(process.handle, (uint8_t*)asm_code.c_str(), asm_code.size()-1, process.start_code_address, 0, &process.insn);
   // cout<<"*************************************************************************************************\n";
//    if (process.asm_count > 0) {
//        size_t j;
 //       for (j = 0; j < process.asm_count; j++) {
      //      printf("0x%"PRIx64":\t%s\t\t%s\n", process.insn[j].address, process.insn[j].mnemonic,
//                process.insn[j].op_str);
//        }
     
     //   cs_free(process.insn, process.asm_count);
//    } else
  //  printf("ERROR: Failed to disassemble given code!\n");
     
  //  cs_close(&process.handle);
//printf("VM_find_process_code out\n");
}

void VM_find_process_date(VM_vmi &vmi_os,VM_process &process)
{	//printf("VM_find_process_date in\n");
	int k=0;
	for (unsigned long i = process.start_date_address; i < process.end_date_address; i+=1){
        if(300<process.date_long||300<(i-process.start_date_address))
            break;
		uint8_t temp=0;
		vmi_read_8_va(vmi_os.vmi, (addr_t)i, process.pid, &temp);
        process.date[process.date_long++] = temp;
    }//printf("VM_find_process_date out\n");
}

void VM_find_process_stack(VM_vmi &vmi_os,VM_process &process)
{/*	printf("VM_find_process_stack in\n");
	int k=0;
	for (unsigned long i = process.start_stack_address; i < process.end_stack_address; i+=1){
        if(300<process.stack_long||300<(i-process.start_stack_address))
            break;
		uint8_t temp=0;
		vmi_read_8_va(vmi_os.vmi, (addr_t)i, process.pid, &temp);printf("%lx ",temp);
        process.stack[process.stack_long++] = temp;   
	}printf("VM_find_process_stack out\n");*/
}


bool get_offset(VM_vmi &vmi_os)
{
    vmi_os. memory = NULL;
    vmi_os. offset=0;
    vmi_os. list_head = 0;
    vmi_os. current_list_entry = 0;
    vmi_os. next_list_entry = 0;
    vmi_os. next_module=0;
    vmi_os. head_module=0;
    vmi_os. current_process = 0;
    vmi_os. head_process=0;
    vmi_os. tmp_next = 0;
    vmi_os. procname = NULL;
    
    vmi_os. pid = 0;

    vmi_os. tasks_offset=0;
    vmi_os. pid_offset=0;
    vmi_os. name_offset=0;
    vmi_os. children_offset=0x448;
    vmi_os. sibling_offset=0x458;
    vmi_os. state_offset=0;
    vmi_os. flag_offset=0x14;
    vmi_os. prio_offset=0x48,
    vmi_os. static_prio_offset=0x4c;
    vmi_os. normal_prio_offset=0x50;
    vmi_os. rt_priority_offset=0x54;
    vmi_os. start_code_offset=0xe8;
    vmi_os. end_code_offset=0xf0;
    vmi_os. start_date_offset=0xf8;
    vmi_os. end_date_offset=0x100;
    vmi_os. start_stack_offset=0x108;
    vmi_os. end_stack_offset=0x110;
    vmi_os. mm_offset=0x380;

    vmi_os. module_state_offset=0;
    vmi_os. module_name_offset=0x10;
    vmi_os. module_version_offset=0xb0;
    vmi_os. module_srcversion_offset=0xc0;
    vmi_os. module_num_syms_offset=0xe0;
    vmi_os. module_list_offset=0x0;
   
    vmi_os. process_number1=0;
    vmi_os. process_number2=0;
    vmi_os. hide_process_pid[500];
    vmi_os. hide_process_number=0;//hide_process_pid[]储存隐藏进程pid

    /*******file_offset***********/
    vmi_os. fs_task_offset=1552;
	vmi_os. dentry_root_fs_offset=32;
	vmi_os. d_parent_dentry_offset=24;
	vmi_os.d_child_dentry_offset=144;
	vmi_os. d_subdirs_dentry_offset=160;
	vmi_os.name_dentry_offset=40;    
	vmi_os. d_inode_dentry_offset=48;
	vmi_os.d_sb_dentry_offset=104;

	vmi_os. imode_inode_offset=0;
	vmi_os. i_uid_inode_offset=4;
	vmi_os. i_bytes_inode_offset=140;
	vmi_os. i_state_inode_offset=160;
	vmi_os. i_atime_sec_inode_offset=88;
	vmi_os. i_ino_inode_offset=64;

	vmi_os. i_gid_inode_offset=8;
	vmi_os. i_flags_inode_offset=12;
	vmi_os. i_rdev_inode_offset=76;
	vmi_os. i_version_inode_offset=320;
	vmi_os. i_count_inode_offset=328;
	vmi_os. i_sb_inode_offset=40;
	vmi_os. s_type_superblock_offset=40;
    vmi_os. name_s_type_offset=0;
    
    /*******************************/
    
    vmi_os.process. code_long = 0;
	vmi_os.process. date_long = 0;	
    vmi_os.process. start_time = 0;	
    
    ///////////////////////////////
    vmi_os.module.name=NULL;
	vmi_os.module.size=0;
	vmi_os.module.used_by_number=0;
	vmi_os.module.version=NULL;
	vmi_os.module.srcversion=NULL;
    ////////////////////////////////

    return true;

}



int VM_vmi_init(char *argv,VM_vmi &vmi_os)
{
    char *name = argv;

    get_offset(vmi_os);


    /* initialize the libvmi library *///初始化vmi
    if (vmi_init(&vmi_os.vmi, VMI_AUTO | VMI_INIT_COMPLETE, name) == VMI_FAILURE) {
        //printf("Failed to init LibVMI library.\n");
        return 1;
    }
    //获取libvmi当前访问的操作系统类型，以及相关联的内存偏移量，有效的偏移量和具体的libvmi.conf配置有关
    if (VMI_OS_LINUX == vmi_get_ostype(vmi_os.vmi)) {
        vmi_os.tasks_offset = vmi_get_offset(vmi_os.vmi, "linux_tasks");
       // printf("tasks_offset=%lx",vmi_os.tasks_offset);
        vmi_os.name_offset = vmi_get_offset(vmi_os.vmi, "linux_name");
        vmi_os.pid_offset = vmi_get_offset(vmi_os.vmi, "linux_pid");

    }

    else if (VMI_OS_WINDOWS == vmi_get_ostype(vmi_os.vmi)) {
        vmi_os.tasks_offset = vmi_get_offset(vmi_os.vmi, "win_tasks");
        if (0 == vmi_os.tasks_offset) {
            //printf("Failed to find win_tasks\n");
            return 1;
        }
        vmi_os.name_offset = vmi_get_offset(vmi_os.vmi, "win_pname");
        if (0 == vmi_os.name_offset) {
      //      printf("Failed to find win_pname\n");
            return 1;
        }
        vmi_os.pid_offset = vmi_get_offset(vmi_os.vmi, "win_pid");
        if (0 == vmi_os.pid_offset) {
            //printf("Failed to find win_pid\n");
            return 1;
        }
    }
    char *name2 = vmi_get_name(vmi_os.vmi);

    if (VMI_FILE != vmi_get_access_mode(vmi_os.vmi)) {
        unsigned long id = vmi_get_vmid(vmi_os.vmi);
    }
    else {
    }
    free(name2);

    if (VMI_OS_LINUX == vmi_get_ostype(vmi_os.vmi)) {
        vmi_os.current_process = vmi_translate_ksym2v(vmi_os.vmi, "init_task");
        vmi_read_addr_ksym(vmi_os.vmi, "modules", &vmi_os.next_module);
    	vmi_os.head_process = vmi_os.current_process;
    	vmi_os.head_module = vmi_os.next_module;
    }
    else if (VMI_OS_WINDOWS == vmi_get_ostype(vmi_os.vmi)) {
        vmi_read_addr_ksym(vmi_os.vmi, "PsInitialSystemProcess\n", &vmi_os.current_process);
    }
}

void get_process_infornmation(VM_vmi &vmi_os,VM_process &process,addr_t current_process,int tree_or_list)
{//printf("get_process_infornmation in\n");
	vmi_read_32_va(vmi_os.vmi, current_process + vmi_os.pid_offset, 0, &vmi_os.pid);//获取当前进程pid
	vmi_read_32_va(vmi_os.vmi, current_process + vmi_os.state_offset, 0, &vmi_os.state);//获取当前进程pid
	vmi_read_32_va(vmi_os.vmi, current_process + vmi_os.flag_offset, 0, &vmi_os.flag);//获取当前进程pid
	vmi_read_32_va(vmi_os.vmi, current_process + vmi_os.prio_offset, 0, &vmi_os.prio);//获取当前进程pid
	vmi_read_32_va(vmi_os.vmi, current_process + vmi_os.static_prio_offset, 0, &vmi_os.static_prio);//获取当前进程pid
	vmi_read_32_va(vmi_os.vmi, current_process + vmi_os.normal_prio_offset, 0, &vmi_os.normal_prio);//获取当前进程pid
	vmi_read_32_va(vmi_os.vmi, current_process + vmi_os.rt_priority_offset, 0, &vmi_os.rt_priority);//获取当前进程pid

	vmi_read_addr_va(vmi_os.vmi, current_process + vmi_os.mm_offset, 0, &vmi_os.mm);//获取当前进程pid
	vmi_read_addr_va(vmi_os.vmi, vmi_os.mm + vmi_os.end_code_offset, 0, &vmi_os.end_code);//获取当前进程pid
    vmi_read_addr_va(vmi_os.vmi, vmi_os.mm + vmi_os.start_code_offset, 0, &vmi_os.start_code);//获取当前进程
    vmi_read_addr_va(vmi_os.vmi, vmi_os.mm + vmi_os.end_date_offset, 0, &vmi_os.end_date);//获取当前进程pid
    vmi_read_addr_va(vmi_os.vmi, vmi_os.mm + vmi_os.start_date_offset, 0, &vmi_os.start_date);//获取当前进程
    vmi_read_addr_va(vmi_os.vmi, vmi_os.mm + vmi_os.end_stack_offset, 0, &vmi_os.end_stack);//获取当前进程pid
    vmi_read_addr_va(vmi_os.vmi, vmi_os.mm + vmi_os.start_stack_offset, 0, &vmi_os.start_stack);//获取当前进程

     vmi_read_addr_va(vmi_os.vmi, current_process + 0x560, 0, &process.start_time);//获取当前进程pid
	process.comm = vmi_read_str_va(vmi_os.vmi, current_process + vmi_os.name_offset, 0);//获取当前进程name

	process.pid = vmi_os.pid;
	process.state = vmi_os.state;
	process.flag = vmi_os.flag;
	process.static_prio = vmi_os.static_prio;
	process.normal_prio = vmi_os.normal_prio;
	process.rt_priority = vmi_os.rt_priority;
	process.start_code_address = vmi_os.start_code;
	process.end_code_address = vmi_os.end_code;
	process.start_date_address = vmi_os.start_date;
	process.end_date_address = vmi_os.end_date;
	process.start_stack_address = vmi_os.start_stack;
	process.end_stack_address = vmi_os.end_stack;
	if (1==tree_or_list)
	{
		vmi_os.num1_pid[vmi_os.process_number1++]= vmi_os.pid;
	}
	if (2==tree_or_list)
	{
       vmi_os.pid_to_process.insert(pair<int,VM_process*>((int)vmi_os.pid,&process));
		vmi_os.num2_pid[vmi_os.process_number2++]= vmi_os.pid;
	}
    VM_find_process_code(vmi_os,process);
    VM_find_process_date(vmi_os,process);
    VM_find_process_stack(vmi_os,process);
//printf("get_process_infornmation out\n");
}


void VM_find_process_tree_dfs(VM_vmi &vmi_os,VM_process &process,addr_t current_process,int b=0) // dfs打印进程树
{//printf("process dfs in\n");
   
	int i;
	static int times=0;
	process.children.next = NULL;
	process.children.pre = NULL;	
	addr_t t,next_list_entry,l;
	vmi_read_32_va(vmi_os.vmi, current_process + vmi_os.pid_offset, 0, &vmi_os.pid);
	get_process_infornmation(vmi_os,process,current_process,2);

 // 	printf("current_process = %lx \n", current_process);
	vmi_read_addr_va(vmi_os.vmi, current_process+vmi_os.children_offset, 0, &next_list_entry);//找到该进程的第一个sibling
	if (0==b)//如果是根节点
	{
		process.parent_pid = process_tree_no_pid;
		process.sibling_pid = process_tree_no_pid;
	}
	
	VM_process *tail_process = NULL;

	 for(t=next_list_entry,i=0;t!=current_process+vmi_os.children_offset;vmi_read_addr_va(vmi_os.vmi, t, 0, &t)){//循环sibling
	   i++;times++;
	   l = t-vmi_os.sibling_offset; //得到进程首地址
		vmi_read_32_va(vmi_os.vmi, l + vmi_os.pid_offset, 0, &vmi_os.pid);
		if (0==vmi_os.pid)
		{
			break;
		}
    	VM_process *temp_process = new VM_process();//构造树
		temp_process->parent_pid = process.pid;
		if (next_list_entry==t){printf("i  %d\n",i);
			process.children.next = &temp_process->sibling;
			process.children.pre = &temp_process->sibling;
			temp_process->sibling.pre = &process.children;
			temp_process->sibling.next = &process.children;
			temp_process->sibling_pid = process_tree_no_pid;

			tail_process = temp_process;

		}else{
			tail_process->sibling.next = &temp_process->sibling;
			temp_process->sibling.pre = &tail_process->sibling;
			temp_process->sibling.next = &process.children;
			process.children.pre = &temp_process->sibling;
			temp_process->sibling_pid = tail_process->pid;

			tail_process = temp_process;
		}
		VM_find_process_tree_dfs(vmi_os,*tail_process,l,b+1);  //dfs
	 }
}

void VM_find_process_tree(VM_vmi &vmi_os,VM_process &process)
{
    printf("*******************dfs**************************\n");
	VM_find_process_tree_dfs( vmi_os,process,vmi_os.head_process,0); // dfs查找树
    printf("****************process tree find ****************\n");
}



int VM_find_process_list(VM_vmi &vmi_os,VM_process &process)
{
  //  printf("********************************************打印链表进程**************************************\n");
    vmi_os.list_head = vmi_os.current_process + vmi_os.tasks_offset;  //保存根进程的成员变量tasks地址，为后面循环跳出做条件
    vmi_os.current_list_entry = vmi_os.list_head;   //保存当前进程的tasks地址
    vmi_os.status = vmi_read_addr_va(vmi_os.vmi, vmi_os.current_list_entry, 0, &vmi_os.next_list_entry);

    get_process_infornmation(vmi_os,process,vmi_os.current_process,1);

    VM_process *tail_process = &process;


     if (vmi_os.procname) {
            free(vmi_os.procname);
            vmi_os.procname = NULL;
        }

    do {
        vmi_os.current_list_entry = vmi_os.next_list_entry;   //令current_list_entry的值等于下一个进程的成员变量tasks的地址
        vmi_os.current_process = vmi_os.current_list_entry - vmi_os.tasks_offset; //获取下一个进程的首地址
    	VM_process *temp_process = new VM_process();
        get_process_infornmation(vmi_os,*temp_process,vmi_os.current_process,1);
        if (!vmi_os.procname) {
        }
        if (vmi_os.procname) {
            free(vmi_os.procname);
            vmi_os.procname = NULL;
        }



        tail_process->tasks.next = &temp_process->tasks;
        process.tasks.pre = &temp_process->tasks;
        temp_process->tasks.next = &process.tasks;
        temp_process->tasks.pre = &tail_process->tasks;

        tail_process = temp_process;
        /************************获取下一个进程的tasks地址赋值给next_list_entry************************/
        vmi_os.status = vmi_read_addr_va(vmi_os.vmi, vmi_os.current_list_entry, 0, &vmi_os.next_list_entry); 


        if (vmi_os.status == VMI_FAILURE) {
            return 1;
        }

    } while (vmi_os.next_list_entry != vmi_os.list_head);
   
}

void printf_process_tree(const VM_process &process,int b){
	int i;
	VM_list_head *temp = NULL;
	VM_process *temp_process=NULL;
	if (process.children.next!=NULL)
	{
		for (temp = process.children.next;temp!=&process.children;temp = temp->next)
		{
			temp_process = VM_list_entry(temp,struct VM_process,sibling);
		}

	}
	
}

int VM_find_process_hide(VM_vmi &vmi_os)
{
    //printf("\n\n\n********************************遍历链表打印进程的id*********************************\n" );
    int i,j,flag1=0,flag;
    // for(i=0;i<vmi_os.process_number1;i++)
    //     printf("%d ",vmi_os.num1_pid[i]);
  //  printf("\n\n\n********************************dfs打印进程树的id************************************ \n");
    // for(i=0;i<vmi_os.process_number2;i++)
    //     printf("%d ",vmi_os.num2_pid[i]);
    
//    printf("\n\n\n********************************对比寻找隐藏进程***************************************\n\n");
    for(i=0;i<vmi_os.process_number1;i++){
        flag = 0;
        for(j=0;j<vmi_os.process_number2;j++){
            if(vmi_os.num1_pid[i]==vmi_os.num2_pid[j]){
                flag = 1;
                break;
            }
        }
        if(0==flag){
      //      printf("%d ",vmi_os.num1_pid[i]);
            flag1 = 1;
        }
    }

    for(i=0;i<vmi_os.process_number2;i++){
        flag = 0;
        for(j=0;j<vmi_os.process_number1;j++){
            if(vmi_os.num2_pid[i]==vmi_os.num1_pid[j]){
                flag = 1;
                break;
            }
        }
        if(0==flag){
            flag1 = 1;
        }
    }
    if (0==flag1)
    {
      //  printf("没有隐藏进程\n");
    }
    printf("\n\n\n**********************Compare ps's pid and link's pid*************************\n\n");
    char vector[200];
	cout<< "这里使用了ss";
    pclose(getTxt("ps", ""));

    FILE* filePoint = fopen("./ps.txt", "r");
    if(NULL == filePoint)
        printf("Not find files!\n");
    else{
        int i = 0, count = 1, pid_ps, hide = 0;
        char* dataHead;
        fgets(vector, 100, filePoint);    //Gave up the first line
        while(0 == feof(filePoint)){
            fgets( vector, 100, filePoint);
            while(' ' == vector[i])
                i++;
            dataHead = vector+i;
            while(' ' != vector[i])
                i++;
            vector[i] = '\0';
            pid_ps = atoi(dataHead);
         //   printf("Compare: %d, %d\n", pid_ps, vmi_os.num1_pid[count]);
            while(pid_ps > vmi_os.num1_pid[count])
            {
              //  printf("Find hide process's pid:%d \n", vmi_os.num1_pid[count]);
                vmi_os.hide_process_pid[vmi_os.hide_process_number++] = vmi_os.num1_pid[count];
                count++; hide++;
                if(count >= vmi_os.process_number1)
                    break;
            }
            count++;
            if(count >= vmi_os.process_number1)
                break;
            i = 0;
        }
        printf("\n Find %d hide process\n", hide);
    }
    printf("\n");
}

vector<VM_process*> cmp_process(VM_vmi &vmi_os)
{
	vector<VM_process* > hid_arry;
	VM_find_process_hide(vmi_os);
	for (int i = 0; i < vmi_os.hide_process_number; ++i)
	{
		map<int, VM_process*>::iterator iter;
	    iter = vmi_os.pid_to_process.find(vmi_os.hide_process_pid[i]); 
	    hid_arry.push_back(iter->second);
	}
	if (1==hid_arry.empty())
	{
		printf("hahah");
	}
	return hid_arry;
}
