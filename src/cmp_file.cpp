// #include "bits/stdc++.h"
// #include "Python.h"
//#include "cmp_file.h"
#include "getTxt.h"
#include "process_list.h"

bool get_root_dentry(VM_vmi& vmi_os)
{
//	cout<<"get_root_dentry"<<endl;
	addr_t temp_name;
	char* filename = NULL;
	addr_t h_fs,h_root,h_dentry,h_d_parent,h_d_child;

    vmi_read_addr_va(vmi_os.vmi, vmi_os.current_process + vmi_os.fs_task_offset , 0, &h_fs);
    vmi_read_addr_va(vmi_os.vmi, h_fs + vmi_os.dentry_root_fs_offset, 0, &h_dentry);
    
    vmi_read_addr_va(vmi_os.vmi,h_dentry+vmi_os.name_dentry_offset,0,&temp_name);
    filename=vmi_read_str_va(vmi_os.vmi,temp_name,0);

 //   cout<<"get vmi_os.root_dentry_addr = "<<h_dentry<<endl;;
    
	vmi_os.root_dentry_addr=h_dentry;

	return true;
}


addr_t get_search_dentry(VM_vmi& vmi_os,string path)
{
	get_root_dentry(vmi_os);
	vector<string> dentry_arry = get_path_arry(path);
	addr_t temp_addr=vmi_os.root_dentry_addr;

	for(int i=0;i<dentry_arry.size();i++)
	{
		cout<<"get ["<<dentry_arry[i]<<"]"<<endl;
		temp_addr=find_dentry_addr(vmi_os,temp_addr,dentry_arry[i]);
	}//printf("exit get_search_dentry\n");
	return temp_addr;
}

addr_t find_dentry_addr(const VM_vmi& vmi_os,addr_t parent_dentry_addr,string dentry_name)
{
	addr_t plist,subdirs_head,temp_name,temp_inode,d_child_list,next_dentry_addr;
	char* filename = NULL;
    vmi_read_64_va(vmi_os.vmi, parent_dentry_addr+vmi_os.d_subdirs_dentry_offset, 0, &subdirs_head);//拿到下一级链表表头

    int i=0;
    plist=subdirs_head;
    vmi_read_addr_va(vmi_os.vmi,plist,0,&plist);
    for(;plist!=subdirs_head;vmi_read_addr_va(vmi_os.vmi,plist,0,&plist))//遍历孩子链表
    {	
        //vmi_read_addr_va(vmi,plist-vmi_os.d_child_dentry_offset,0,&next_dentry_addr);//拿到下一个dentry
        if(plist-vmi_os.d_child_dentry_offset+vmi_os.d_inode_dentry_offset!=0)
        vmi_read_addr_va(vmi_os.vmi,plist-vmi_os.d_child_dentry_offset+vmi_os.d_inode_dentry_offset,0,&temp_inode);
    	if(temp_inode>0)
    	{
    		vmi_read_addr_va(vmi_os.vmi,plist-vmi_os.d_child_dentry_offset+vmi_os.name_dentry_offset,0,&temp_name);
		    filename=vmi_read_str_va(vmi_os.vmi,temp_name,0);
		    if(filename==dentry_name)  
	    	{
	    		return plist-vmi_os.d_child_dentry_offset;
	    	} 
		    //if(strcmp(filename,"bin")==0)  break;
    	}
    }
}

bool get_file_info(VM_vmi& vmi_os,VM_file* newNode,unsigned long temp_inode)
{//printf("get_file_info in\n");
    vmi_read_64_va(vmi_os.vmi,temp_inode+vmi_os.i_ino_inode_offset,0,&(newNode->id));
    vmi_read_16_va(vmi_os.vmi,temp_inode+vmi_os.i_bytes_inode_offset,0,&(newNode->bytes));
    vmi_read_16_va(vmi_os.vmi,temp_inode+vmi_os.imode_inode_offset,0,&(newNode->mode));
    vmi_read_64_va(vmi_os.vmi,temp_inode+vmi_os.i_state_inode_offset,0,&(newNode->state));
    vmi_read_32_va(vmi_os.vmi,temp_inode+vmi_os.i_uid_inode_offset,0,&(newNode->user_id));

    vmi_read_32_va(vmi_os.vmi,temp_inode+vmi_os.i_gid_inode_offset,0,&(newNode->i_gid));
    vmi_read_32_va(vmi_os.vmi,temp_inode+vmi_os.i_flags_inode_offset,0,&(newNode->i_flags));
    vmi_read_32_va(vmi_os.vmi,temp_inode+vmi_os.i_rdev_inode_offset,0,&(newNode->i_rdev));
    vmi_read_32_va(vmi_os.vmi,temp_inode+vmi_os.i_version_inode_offset,0,&(newNode->i_version));
    vmi_read_32_va(vmi_os.vmi,temp_inode+vmi_os.i_count_inode_offset,0,&(newNode->i_count));

    //vmi_read_32_va(vmi_os.vmi,temp_inode+);
    
    unsigned long ttemp;
    vmi_read_64_va(vmi_os.vmi,temp_inode+vmi_os.i_atime_sec_inode_offset,0,&(ttemp));
    time_t tTime=(time_t)ttemp;
    struct tm* tmtime=localtime(&tTime);
    newNode->mtime=asctime(tmtime);
 //   printf("get_file_info out\n");
}

vector<string> get_path_arry(string path)
{
	cout<<path<<endl;

	vector<string> dentry_arry;
	string str;
	for(int i=1;i<path.length();i++)
	{	
		if(path[i]=='/')  
		{
			dentry_arry.push_back(str);
			str.clear();
			continue;
		}
		str+=path[i];
	}
	return dentry_arry;
}


void do_dfs(VM_vmi& vmi_os,addr_t subdirs_head,VM_file* parentNode,int deep)
{//printf("do_dfs in\n");
	addr_t plist,temp_name,temp_inode;
	char* filename = NULL;

	plist=subdirs_head;
    vmi_read_addr_va(vmi_os.vmi,plist,0,&plist);

	VM_file* tail;
	int flag=0;
    for(;plist!=subdirs_head;vmi_read_addr_va(vmi_os.vmi,plist,0,&plist))//遍历孩子链表
    { 	
    	vmi_read_addr_va(vmi_os.vmi,plist-vmi_os.d_child_dentry_offset+vmi_os.d_inode_dentry_offset,0,&temp_inode);
    	if(temp_inode>0)
    	{		
     		vmi_read_addr_va(vmi_os.vmi,plist-vmi_os.d_child_dentry_offset+vmi_os.name_dentry_offset,0,&temp_name);
		    filename=vmi_read_str_va(vmi_os.vmi,temp_name,0);
		  //  printf("filename %s\n", filename);
		    if(filename)
		    {
				VM_file* newNode=new VM_file();
				newNode->name=filename;
	//			cout<<"newNode->name"<<newNode->name;
				get_file_info(vmi_os,newNode,temp_inode);
				if(0==flag){//printf("000\n");
					parentNode->subdirs.pre=&(newNode->bro);
					parentNode->subdirs.next=&(newNode->bro);//父目录向下指
					newNode->bro.next=&(parentNode->subdirs);
					newNode->bro.pre =&(parentNode->subdirs);
				}
				else{//printf("111\n");
					tail->bro.next=&(newNode->bro);
					newNode->bro.pre=&(tail->bro);
					newNode->bro.next=&(parentNode->subdirs);
					parentNode->subdirs.next->pre=&(newNode->bro);
				}
				flag=1;

				tail=newNode;
				//printf("aaa\n");
			//	for(int i=0;i<deep;i++)  cout<<"    ";
				//cout<<"--"<<deep<<" "<<"("<<i<<")"<<" "<<newNode->name<<endl;

				// for(int i=0;i<file_vector.size();i++)
				// if(find(file_vector.begin(),file_vector.end(),filename)==file_vector.end()){
				// 	cout<<"@@@@@@@@@@@@@@@@@@@@@@ "<<filename<<" this is hidden file"<<endl;
				// 	newNode->ishidden=1;
				// }else   newNode->ishidden=0;
				
				addr_t temp_subdirs;
				vmi_read_64_va(vmi_os.vmi,plist-vmi_os.d_child_dentry_offset+vmi_os.d_subdirs_dentry_offset, 0, &temp_subdirs);//拿到下一级链表表头
				if(temp_subdirs!=(plist-vmi_os.d_child_dentry_offset+vmi_os.d_subdirs_dentry_offset))//有下一级目录才递归
				{
					do_dfs(vmi_os,temp_subdirs,newNode,deep+1);
				}
		 	}
    	}
    }
}


void init_file_tree(VM_vmi& vmi_os,string path)
{
//	cout<<"/***************************tree_dfs******************************/"<<endl;
	addr_t search_dentry=get_search_dentry(vmi_os,path);

	addr_t subdirs_head;

	vmi_read_64_va(vmi_os.vmi,search_dentry+vmi_os.d_subdirs_dentry_offset,0,&subdirs_head);
//	printf("subdirs_head = %lx\n", subdirs_head);
	addr_t temp_inode,temp_name;
	vmi_read_64_va(vmi_os.vmi,search_dentry+vmi_os.d_inode_dentry_offset,0,&temp_inode);
	vmi_read_addr_va(vmi_os.vmi,search_dentry+vmi_os.name_dentry_offset,0,&temp_name);
	vmi_os.file_root.name=vmi_read_str_va(vmi_os.vmi,temp_name,0);
	get_file_info(vmi_os,&(vmi_os.file_root),temp_inode);

//	cout<<vmi_os.file_root.name;
//	printf("do_dfs\n");
	do_dfs(vmi_os,subdirs_head,&(vmi_os.file_root),0);

//	cout<<"/*****************************************************************/"<<endl;

}

vector<VM_file*> cmp_file(VM_vmi& vmi_os,char* path)
{
//	cout<<"++++++++++++++++++++++"<<endl;

	pclose(getTxt("tree", path));
	
//	cout<<"cmp_file"<<endl;
	FILE* fp;

//	cout<<"$$$$$$$$"<<endl;
	freopen("tree.txt", "r", stdin);
//	cout<<"_________________"<<endl;
	int num;
    string filename,name;
    vector<string> vm;


    cin>>filename;
 //   cout<<"}}}}}}}}}}}}}}"<<endl;
    cin.ignore();
    cin.clear();
    while(cin>>filename)
    {
    //	cout<<"************"<<endl;
    	vm.push_back(filename);
    }
	fclose(stdin);
    	


//	cout<<"@@@@@@@@@@@@@@@";
//	for(int i=0;i<vm.size();i++)   cout<<vm[i]<<endl;


	vm.erase(vm.end()-1);
	vm.erase(vm.end()-2);

	 init_file_tree(vmi_os,path);//构建树并对比查找树

	return dfs_cmp_file(&(vmi_os.file_root),0,vm);
}


void traverse_file_tree(VM_file* fileNode,int deep)
{
	VM_list_head* p;
    for(p=fileNode->subdirs.next;p!=&(fileNode->subdirs);p=p->next){
		VM_file* tempNode=VM_list_entry(p,struct VM_file,bro);
//		for(int i=0;i<deep;i++)  cout<<"  ";
		
//		cout<<tempNode->name<<" "<<tempNode->id<<" "<<tempNode->s_type<<endl;
				
		if(tempNode->subdirs.next)
		{
			traverse_file_tree(tempNode,deep+1);
		}		
	}

}

vector<VM_file*> dfs_cmp_file(VM_file* fileNode,int deep,vector<string>& file_vector)
{
	vector<VM_file* > hid_arry;

	for(int i=0;i<file_vector.size();i++)	
	{
	    cout<<file_vector[i]<<endl;
	}
        cout<<"%%%%%%%%%%%%%%%%%%%%%%%%\n";
	VM_list_head* p;
    for(p=fileNode->subdirs.next;p!=&(fileNode->subdirs);p=p->next){
		VM_file* tempNode=VM_list_entry(p,struct VM_file,bro);
		for(int i=0;i<deep;i++)  cout<<"  ";
		cout<<tempNode->name<<endl;

		if(find(file_vector.begin(),file_vector.end(),tempNode->name)==file_vector.end()){
	//		cout<<"@@@@@@@@@@@@@@@@@@@@@@ "<<tempNode->name<<" this is hidden file"<<endl;
			tempNode->ishidden=1;
			hid_arry.push_back(tempNode);
	                cout<<"***************************8is hidden file "<< tempNode->name<<"\n";

		}else {//cout<<tempNode->name<<"is not hidden file"<<"\n";
			 tempNode->ishidden=0;
		} 
				
		if(tempNode->subdirs.next)
		{
			dfs_cmp_file(tempNode,deep+1,file_vector);
		}		
	}

	return hid_arry;
}




// bool do_ls(VM_vmi& vmi_os,addr_t ls_addr)
// {
// 	cout<<"do_ls\n";
// 	/*******/
	
// 	addr_t plist,subdirs_head,temp_name,temp_inode,d_child_list,next_dentry_addr;
// 	char* filename = NULL;
// 	vmi_read_64_va(vmi_os.vmi, ls_addr+vmi_os.d_subdirs_dentry_offset, 0, &subdirs_head);//拿到下一级链表表头
	
//     int i=0;
//     plist=subdirs_head;
//     vmi_read_addr_va(vmi_os.vmi,plist,0,&plist);
//     vmi_read_addr_va(vmi_os.vmi,plist,0,&plist);

//     /*初始化头节点*/
//     vmi_read_addr_va(vmi_os.vmi,plist-vmi_os.d_child_dentry_offset+vmi_os.d_inode_dentry_offset,0,&temp_inode);
//     vmi_read_addr_va(vmi_os.vmi,plist-vmi_os.d_child_dentry_offset+vmi_os.name_dentry_offset,0,&temp_name);
// 	filename=vmi_read_str_va(vmi_os.vmi,temp_name,0);
// 	vmi_os.file_list_head.name=filename;
//     get_file_info(vmi_os,&vmi_os.file_list_head,temp_inode);

//     VM_file* tail=&(vmi_os.file_list_head);

//     for(;plist!=subdirs_head;vmi_read_addr_va(vmi_os.vmi,plist,0,&plist))//遍历孩子链表
//     { 	
//         //vmi_read_addr_va(vmi,plist-vmi_os.d_child_dentry_offset,0,&next_dentry_addr);//拿到下一个dentry
//         if(plist-vmi_os.d_child_dentry_offset+vmi_os.d_inode_dentry_offset!=0)
//         	vmi_read_addr_va(vmi_os.vmi,plist-vmi_os.d_child_dentry_offset+vmi_os.d_inode_dentry_offset,0,&temp_inode);
//     	if(temp_inode>0)
//     	{		
//      		vmi_read_addr_va(vmi_os.vmi,plist-vmi_os.d_child_dentry_offset+vmi_os.name_dentry_offset,0,&temp_name);
// 		    filename=vmi_read_str_va(vmi_os.vmi,temp_name,0);
// 		    if(filename)
// 		    {
// 			    /****************************************/
// 			    VM_file* newNode=new VM_file();
// 			    newNode->name=filename;
// 			    get_file_info(vmi_os,newNode,temp_inode);

// 			    newNode->f_child.next=&(vmi_os.file_list_head.f_child);
// 			    vmi_os.file_list_head.f_child.pre=&(newNode->f_child);
// 			    newNode->f_child.pre=&(tail->f_child);
// 			    tail->f_child.next=&(newNode->f_child);

// 			    tail=newNode;
// 			    /****************************************/
// 			    //if(strcmp(filename,"bin")==0)  break;
// 		 	}	
//     	}
//     }
//     return true;
// }



/*
bool walk_flist(const VM_vmi& vmi_os)
{
	cout<<"walk flist\n";

	VM_list_head *l;
	VM_list_for_each(l,&(vmi_os.file_list_head.f_child))
	{
		VM_file* temp=VM_list_entry(l,struct VM_file,f_child);
        //struct tm;
        //cout<<temp->mtime;
		cout<<temp->name<<" "<<temp->id<<" "<<temp->mode<<" "<<temp->bytes<<" "<<temp->state<<" "<<temp->mtime<<endl;
	}


	return true;
}

vector<VM_file*> cmp_ls(const VM_vmi& vmi_os,char* path)
{

	vector<VM_file*> hid_arry;
	vector<int> vm;
	cout<<"cmp_ls\n";

	pclose(getTxt("ls", path));
    // char a[100];
    // fgets(a, 100, er);
    // a[99] = '\0';
    // cout<< a<< endl<<endl;
    // pclose(er);
	
	freopen("ls.txt", "r", stdin);
	int num;
    string name;
    while(cin>>num>>name)
    {
    	vm.push_back(num);
    }
    fclose(stdin);

    VM_list_head *l;
	VM_list_for_each(l,&(vmi_os.file_list_head.f_child))
	{
		VM_file* temp=VM_list_entry(l,struct VM_file,f_child);
		if(find(vm.begin(),vm.end(),temp->id)==vm.end())
		{
			hid_arry.push_back(temp);
		}
   	}
	return hid_arry;
}

bool cmp_file(VM_vmi& vmi_os,char* path)
{
	cout<<"cmp_file"<<endl;
	addr_t search_dentry=get_search_dentry(vmi_os,path);

	do_ls(vmi_os,search_dentry);

	vector<VM_file*> hid_arry=cmp_ls(vmi_os,path);//

	if(hid_arry.empty())
	{
		cout<<"no hidden file"<<endl;
	}else{

		for(int i=0;i<hid_arry.size();i++)  
			cout<<"find a hid "<<hid_arry[i]->name<<hid_arry[i]->id<<endl;
	}

	return true;

}

*/
