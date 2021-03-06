#include "OS.h"
# include <string> 

//进入下一级目录
int goNextDir(string filename){
	int pos = -1;
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); i++){
		if (fileSystem.sfd[cur_SFD].sfdVec[i].name == filename){
			pos = i;
			break;
		}
	}
	if (pos == -1){
		textcolor(12);
		cout << "不存在的目录，操作失败！\n";
		return 0;
	}

	int cur_iNode = fileSystem.sfd[cur_SFD].sfdVec[pos].id;
	if (fileSystem.iNode[cur_iNode].type == 0){
		textcolor(12);
		cout << "输入的为文件名，操作失败！\n";
		return 0;
	}
	cur_SFD = fileSystem.iNode[cur_iNode].sfd_id;
	return 1;
}


//获得当前目录的i结点号
int getInodeNum(){
	int pos = -1;
	for (int i = 0; i < 128; i++){
		if (iNode[i] == 0 && fileSystem.iNode[i].sfd_id == cur_SFD){
			pos = i;
			break;
		}
	}
	return pos;
}

//显示当前目录下的所有文件及目录
void showSFD(){
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); i++){
		cout << fileSystem.sfd[cur_SFD].sfdVec[i].name << "\t\t";
		int id = fileSystem.sfd[cur_SFD].sfdVec[i].id;
		if (fileSystem.iNode[id].type == 0){
			cout << "file" << endl;
		}
		else
		{
			
			cout << "dir" << endl;
		}
	}
	cout << endl;
}

void find_filedir(string cur_path, string name)
{
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); ++i){
		if (fileSystem.sfd[cur_SFD].sfdVec[i].name == name){
			cout <<name<< "\t\t" <<cur_path<< " " <<name<< endl;
	        break;
	        
		}
	}
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); ++i){
		if (fileSystem.sfd[cur_SFD].sfdVec[i].id != -1){
			int temp_SFD = cur_SFD;
			cur_SFD = fileSystem.iNode[fileSystem.sfd[cur_SFD].sfdVec[i].id].sfd_id;
			cur_path=cur_path + fileSystem.sfd[temp_SFD].sfdVec[i].name;
			find_filedir(cur_path, name);
			cur_SFD = temp_SFD;
		}
	}
}

