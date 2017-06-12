#include <stdio.h>
#include<stdlib.h>
#define N 10

float stamp_time = 4;


typedef	struct  Process
{
	float start_time;
	float should_serve_time;
	float had_serve_time;
	float end_time;
	float run_time;
	float weighted_run_time;
	int finished;

} Process;

typedef Process* PProcess;

typedef enum RETURN_STATUS {
	 FINISH,
	INTERUPT,
	 USED,
     UNSED,
} STATUS;

STATUS run(PProcess pprocess, float* now_time) {
	pprocess->had_serve_time += stamp_time;
		(*now_time) += stamp_time;
	if (pprocess->had_serve_time >= pprocess->should_serve_time) {
		pprocess->finished = 1;
		float left_time = pprocess->had_serve_time\
                          -pprocess->should_serve_time ;
		(*now_time) -=left_time;
		pprocess->end_time = (*now_time);
		return FINISH;
	} else {
		// pprocess->had_serve_time+=stamp_time;
		return INTERUPT;
	}
}



void init_processes(PProcess pprocess, int num, float processes_table[][2]) {
	PProcess current_proc = NULL;
	// float* current_proc_table = processes_table;
	int index = 0;
	while (index < num) {
		current_proc = pprocess + index;
		current_proc->start_time = processes_table[index][0];
		current_proc->should_serve_time = processes_table[index][1];
		// init state is unfinished
		current_proc->finished = 0;
        current_proc->had_serve_time=0;
        current_proc->run_time=0;
        current_proc->weighted_run_time=0;
        current_proc->end_time=0;
        index++;
	}
}



void post_analyze_process(PProcess pprocess, int num_processes) {
 int index= 0;
 PProcess current_pprocess=NULL;
 while(index<num_processes){
     current_pprocess = pprocess+index;
   current_pprocess->run_time=current_pprocess->end_time-current_pprocess->start_time;
   current_pprocess->weighted_run_time = current_pprocess->run_time / current_pprocess->should_serve_time;
   index++;
 }
}

void display_processes(PProcess pprocess, int num_processes){
   int index=0;
   PProcess current_pprocess =NULL;
   printf("pid\tstart time\tserve time\tend time\trun time\tweighted time\n");
   while(index<num_processes){
    current_pprocess =pprocess+index;
    printf("%d\t%f\t%f\t%f\t%f\t%f\n",index,current_pprocess->start_time,current_pprocess->should_serve_time,current_pprocess->end_time,current_pprocess->run_time,current_pprocess->weighted_run_time);
    index++;
   }
}
void  mock_data(float processes_table[][2]){
    processes_table[0][0]=0;
    processes_table[0][1]=3;
    processes_table[1][0]=2;
    processes_table[1][1]=6;
    processes_table[2][0]=4;
    processes_table[2][1]=4;
    processes_table[3][0]=6;
    processes_table[3][1]=5;
    processes_table[4][0]=8;
    processes_table[4][1]=2;
}


int check_process(PProcess current_pprocess, int now_time){
	if (current_pprocess->finished ||	current_pprocess->start_time>now_time){
    return 0;
    }
    if(current_pprocess->start_time<now_time &&current_pprocess->had_serve_time==0){
    current_pprocess->start_time=now_time;
    }
    return 1;
}

int main() {
	int num_processes = 5;
	Process processes[10];

    float processes_table[N][2];
   mock_data(processes_table);
	init_processes(processes, num_processes, processes_table);

	float now_time = 0;
	int current_index = 0;
	PProcess current_pprocess = NULL;

	int num_processes_finished = 0;
	STATUS status;

	while (num_processes_finished < num_processes) {
        status=INTERUPT;
		current_pprocess = processes + current_index;
        if(check_process(current_pprocess,now_time)){
			status = run(current_pprocess, &now_time);
        }

		if (status == FINISH) {
		    num_processes_finished++;
		} else if (status == INTERUPT) {

		} else {
			printf("unknown status!\n");
			exit(-1);
		}
		current_index += 1;
		if (current_index + 1 > num_processes) {
			current_index = 0;
		}
	}
    post_analyze_process(processes,num_processes);
    display_processes(processes,num_processes);
    return 0;
}
