//#include "module.h"
#include "getTxt.h"
#include "process_list.h"
#include <capstone/capstone.h>
#include "Features.h"
vector<VM_module*> cmp_lsmod(VM_vmi &vmi_os)
{
//	printf("cmp_lsmod\n");
    VM_module_init(vmi_os.module);
    VM_find_modules_list(vmi_os,vmi_os.module);
    walk_module(vmi_os);

//	cout<<"cmp_lsmod\n";
	vector<string> v;
	vector<VM_module* > hid_arry;
	pclose(getTxt("lsmod",""));
	// char a[100];
 //    fgets(a, 100, er);
 //    a[99] = '\0';
 //    cout<< a<< endl<< endl;
 //    pclose(er);

	FILE* fp;
	if((fp=fopen("lsmod.txt","r"))==0){
		cout<<"open lsmod error"<<endl;
		return  hid_arry;
	}

	char chr[100];

	while(feof(fp)==0)
	{
		fgets(chr,100,fp);
		for (int i=0; i < 100; i++) {
			if (chr[i] == ' ') {
				chr[i] = '\n';
				break;
			}
		}
		v.push_back(chr);
	}




	VM_list_head* l;
	int flag=0;
	VM_list_for_each(l,&(vmi_os.module.list))
	{
		VM_module* temp=VM_list_entry(l,struct VM_module,list);

		size_t i=0;
		for(;i<v.size();i++) 
		{
			if (v[i] == temp->name)
				hid_arry.push_back(temp);
		}
	}

	if(hid_arry.empty())   cout<<"no hidden module\n";
	else   for(size_t i=0;i<hid_arry.size();i++)   cout<<"find a hidden module :"<<hid_arry[i]->name<<endl;

	cout<<"***********\n\n";
	return hid_arry;
}


bool walk_module(VM_vmi &vmi_os)
{
//	cout<<"walk_module"<<endl;

    VM_module *temp_module = &vmi_os.module;
     do{  
         printf("%s\n", temp_module->name);     
         temp_module = VM_list_entry(temp_module->list.next,struct VM_module,list);
     } while(&vmi_os.module.list!=&temp_module->list);
}

int VM_module_init(VM_module &module)
{
	module.list.next = &module.list;
	module.list.pre = &module.list;
}

void VM_find_modules_list(VM_vmi &vmi_os,VM_module &module)
{	
	addr_t tmp_next = 0;
	vmi_read_addr_va(vmi_os.vmi, vmi_os.next_module, 0, &tmp_next);
	get_module_info(vmi_os,module,vmi_os.next_module);
	VM_module* tail_module = &module;
	vmi_os.next_module = tmp_next;
	do {vmi_read_addr_va(vmi_os.vmi, vmi_os.next_module, 0, &tmp_next);
		VM_module* temp_module = new VM_module();

        if (vmi_os.head_module == tmp_next)
        {
        	break;
        }
        get_module_info(vmi_os,*temp_module,vmi_os.next_module);

        vmi_read_addr_va(vmi_os.vmi, vmi_os.next_module, 0, &tmp_next);
        tail_module->list.next = &temp_module->list;
		temp_module->list.pre = &tail_module->list;
		module.list.pre = &temp_module->list;
		temp_module->list.next = &module.list;
        vmi_os.next_module = tmp_next;
        tail_module = temp_module;
    }while (vmi_os.head_module != tmp_next);
}

void get_module_info(VM_vmi &vmi_os,VM_module &module,addr_t current_module)
{
	uint64_t a;
	string asm_code;
	int k=0;
	addr_t temp_address;
	vmi_read_64_va(vmi_os.vmi, current_module +0xb0, 0, &temp_address);//verision
	module.version = vmi_read_str_va(vmi_os.vmi,temp_address, 0);
	//if(module.version!=NULL)
	//	printf("%s\n",module.version);

	vmi_read_64_va(vmi_os.vmi, current_module +0xb8, 0, &temp_address);//srcverision
	module.srcversion = vmi_read_str_va(vmi_os.vmi,temp_address, 0);
	//if(module.srcversion!=NULL)
	//	printf("%s\n",module.srcversion);

	vmi_read_64_va(vmi_os.vmi, current_module +0x2a8, 0, &temp_address);//args
	module.args = vmi_read_str_va(vmi_os.vmi,temp_address, 0);
	//if(module.args!=NULL)
	//	printf("%s\n",module.args);

	vmi_read_32_va(vmi_os.vmi, current_module +0x1c0, 0, &module.size);//size
	vmi_read_32_va(vmi_os.vmi, current_module +0x1c4, 0, &module.text_size);//size
	

	vmi_read_64_va(vmi_os.vmi, current_module +0x330, 0, &module.init_code_address);//获取当前进程pid
	for(unsigned long i=module.init_code_address;i<module.init_code_address+500;i++){
		uint8_t tmp;
		vmi_read_8_va(vmi_os.vmi, i, 0, &tmp);//获取当前进程pid
		module.code[k++] = tmp;
		asm_code+=tmp; 
	//	printf("0x%lx, ",tmp);
	}//printf("\n");
	module.rootkid = CheckMalsoftware_(module.code,23);
	//if(NULL!=module.rootkid)
	//	printf("````````````````%s\n",module.rootkid->name);
	module.name = vmi_read_str_va(vmi_os.vmi,current_module + 0x10, 0);
	printf("name = %s\n",module.name);


	if (cs_open(CS_ARCH_X86, CS_MODE_64, &module.handle) != CS_ERR_OK)
        return ;
    module.asm_count = cs_disasm(module.handle, (uint8_t*)asm_code.c_str(), asm_code.size()-1, module.init_code_address, 0, &module.insn);
	
}

bool get_vm_list(VM_list_vm *v) {
	pclose(getTxt("xl", ""));

	// VM_list_vm v[100];
	size_t i = 0;
	

	freopen("xl.txt", "r", stdin);
	string name;
	int cpu, id, mem;
	string stat;
	double time;
	cin.clear();
	cin.ignore();
	cin>> name>> name>> name>> name>> name>> name;
	while (cin>> name>> id>> mem>> cpu>> stat>> time) {
		// cout<< name<< " "<< id<< " "<< mem<< " " << cpu<< " "<< stat<< " "<< time<< "\n";
		v[i].name = name;
		v[i].id = id;
		v[i].mem = mem;
		v[i].cpu = cpu;
		v[i].stat = stat;
		v[i++].time = time;
	}
	v[0].num = i;
	cin.clear();
	cin.ignore();
	fclose(stdin);
	return true;
}

bool print_XL_list() {
	VM_list_vm v[100];
	get_vm_list(v);
	for (size_t i = 0; i < v[0].num; i++) {
	//	cout<< v[i].name<< " "<< v[i].id<< " "<< v[i].cpu<< "\n";
	}
}
