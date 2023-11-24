#include "main.h"

#define kan prev->prev 
#define kan2 prev->next
class imp_res : public Restaurant
{
	public:
		customer *head;
		customer *tail_order;
		customer *wait;
		customer *wait_tail;
		customer *temp;
		int num_cus,num_wait,sum_cus;
		imp_res() {
			head=nullptr;
			wait=nullptr;
			wait_tail=nullptr;
			tail_order=nullptr;
			temp=nullptr;
			num_cus=0;
			num_wait=0;
			sum_cus=0;
		};

		~imp_res(){
	            customer* temp_temp=temp;
				if(temp_temp) temp_temp->kan->next=nullptr;
	            while(temp_temp){
	                temp=temp->next;
					temp_temp->next=nullptr;
					temp_temp->prev=nullptr;
	                delete temp_temp;
	                temp_temp=temp;
	            }
	            temp_temp=wait;
	            while(temp_temp){
	                wait=wait->next;
	                delete temp_temp;
	                temp_temp=wait;
	            };
	            temp_temp=head;
	            while(temp_temp){
	                delete temp_temp->prev;
	                head=head->next;
	                delete temp_temp;
	                temp_temp=head;
	            };
	        }
		void RED(string name, int energy)	//Handle Red
		{
			customer *cus = new customer (name, energy, nullptr, nullptr);
			if(cus->energy==0){
				delete cus;
				return;
			}
			else if(num_cus>=0){
				customer* temp2= head;
				while(temp2!=nullptr){
					if(cus->name==temp2->name&&!temp2->kan&&num_cus<MAXSIZE&&(num_wait==0||cus->name!=wait->name)){
						if(this->temp==nullptr){
							this->temp=cus;
							cus->prev=temp2->prev;
							temp->next=temp;
							cus->kan=cus;
							cus->prev->name="desk";
							num_cus++;
							return;
						}
						else if(num_cus<MAXSIZE/2){
							if(cus->energy>=temp->energy){
								cus->prev=temp2->prev;
								cus->prev->name="desk";
								cus->kan=temp;
								cus->next=temp->next;
								cus->next->kan=cus;
								temp->next=cus;
							}
							else{
								cus->prev=temp2->prev;
								cus->prev->name="desk";
								cus->kan=temp->kan;
								cus->kan->next=cus;
								temp->kan=cus;
								cus->next=temp;
							};
							num_cus++;
							temp=cus;
						}
						else{
							customer* temp3=temp;
							customer* current=temp;
							int RES=abs(temp->energy-cus->energy);
							int res_check=cus->energy-temp->energy;   
							temp3=temp;

							for(int i=0;i<num_cus;++i){	
								res_check=cus->energy-temp3->energy;
								if(RES<abs(res_check)){
									RES=abs(res_check);
									current=temp3;
								};
								temp3=temp3->next;
							};

							if (cus->energy-current->energy>=0){	
								cus->prev=temp2->prev;
								cus->prev->name="desk";	
								cus->next=current->next;
								cus->next->kan=cus;
								current->next=cus;
								cus->kan=current;
							}
							else{
								cus->prev=temp2->prev;
								cus->prev->name="desk";
								cus->kan=current->kan;
								cus->kan->next=cus;
								current->kan=cus;
								cus->next=current;
							};
							num_cus++;
							temp=cus;
						}
						return;
					}
					else if(cus->name==temp2->name){
						delete cus;
						return;
					}
					temp2=temp2->next;
				}
			}
			// 
			if(num_cus<MAXSIZE)  
			{
				if(this->temp==nullptr){
					this->temp=cus;
					temp->next=temp;
					customer* check=new customer("desk",sum_cus++,temp,nullptr);
					this->head=new customer (cus->name, cus->energy, check, nullptr);
					this->tail_order=head;
					temp->prev=check;
					num_cus++;
					return;
				}
				else if(num_cus<MAXSIZE/2){
					if(cus->energy>=temp->energy){
					    customer* check=new customer("desk",sum_cus++,temp,tail_order);
						tail_order->next=new customer (cus->name, cus->energy, check,nullptr);
						tail_order=tail_order->next;
						cus->next=temp->next;
						cus->next->kan=cus;
						temp->next=cus;
						cus->prev=check;
					}
					else{
						customer* check=new customer("desk",sum_cus++,temp->kan,tail_order);
						tail_order->next=new customer (cus->name, cus->energy, check,nullptr);
						tail_order=tail_order->next;
						cus->prev=check;
						cus->kan->next=cus;
						temp->kan=cus;
						cus->next=temp;
					};

					temp=cus;
					num_cus++;
				}
				else{
					customer* temp2=temp;
					customer* current=temp;
					int RES=abs(temp->energy-cus->energy);
					int res_check=cus->energy-temp->energy;   
					temp2=temp;

					for(int i=0;i<num_cus;++i){	
						res_check=cus->energy-temp2->energy;
						if(RES<abs(res_check)){
							RES=abs(res_check);
							current=temp2;
						};
						temp2=temp2->next;
					};

					if (cus->energy-current->energy>=0){	
						customer* check=new customer("desk",sum_cus++,current,tail_order);
						tail_order->next=new customer (cus->name, cus->energy, check,nullptr);
						tail_order=tail_order->next;
						cus->next=current->next;
						cus->next->kan=cus;
						current->next=cus;
						cus->prev=check;			
					}
					else{
						customer* check=new customer("desk",sum_cus++,current->kan,tail_order);
						tail_order->next=new customer (cus->name, cus->energy, check,nullptr);
						tail_order=tail_order->next;
						cus->prev=check;
						cus->kan->next=cus;
						current->kan=cus;
						cus->next=current;
					};
					num_cus++;
					temp=cus;
				}
			}
			else if(num_wait<MAXSIZE){
				if(wait==nullptr){
					wait=cus;
					wait_tail=cus;
					num_wait++;
					wait->prev=new customer("wait",sum_cus++,nullptr,tail_order);
					tail_order->next=new customer(wait->name,wait->energy,wait->prev,nullptr);
					tail_order=tail_order->next;
					wait->next=nullptr;
				}
				else{
					wait_tail->next=cus;
					num_wait++;
					cus->prev=new customer("wait",sum_cus++,wait_tail,tail_order);
					tail_order->next=new customer(cus->name,cus->energy,cus->prev,nullptr);
					tail_order=tail_order->next;
					wait_tail=wait_tail->next;
				}
			}
			else{
				delete cus;
				return;
			}
		} //End Red

		void addWaitCus(){
			while (num_cus<MAXSIZE&&num_wait!=0){
				string temp_name=wait->name;
				int temp_en=wait->energy;
				num_wait--;
				if(num_wait==0){
					wait->kan=nullptr;
					wait->next=nullptr;
					delete wait;
					wait=nullptr;
					wait_tail=nullptr;
				}
				else{
					customer* temp_wait=wait;
					wait=wait->next;
					temp_wait->next=nullptr;
					temp_wait->kan=nullptr;
					wait->kan=nullptr;
					delete temp_wait;
				}
				this->RED(temp_name,temp_en);
			}
			if(num_wait==0) sum_cus=0;
		}
		void BLUE(int num)
		{
	        if(num_cus==0&&num_wait==0) return;
			for(int i=0;i<num;i++){
				if(num_cus==0) break;
				customer* temp_head=head;
				while(temp_head->prev->name!="desk"){
					temp_head=temp_head->next;
				}
				if (temp_head != nullptr){
					customer* temp_temp=temp_head->kan->next;
					temp=temp_temp->energy>0?temp_temp->next:temp_temp->kan;
					temp_temp->next->kan=temp_temp->kan;
					temp_temp->kan->next=temp_temp->next;
					delete temp_temp;
					num_cus--;
					temp_head->kan=nullptr;
					if(num_cus==0){
						temp=nullptr;
					}
					if(temp_head->kan2){
						temp_head->kan2->next=temp_head->next;
						if(temp_head->next){
							temp_head->next->kan2=temp_head->kan2;
						}
						else tail_order=temp_head->kan2;
					}
					else{
						if(temp_head->next){
							head=temp_head->next;
							temp_head->next->kan2=nullptr;
						}
						else {
							head=nullptr;
							tail_order=nullptr;
							sum_cus=0;
						}
					};
					delete temp_head->prev;
					delete temp_head;
				};
				if(head) head->kan2=nullptr;
				else break;
			};
			addWaitCus();
		}
		//  Start Purple
		void swap_custormer(customer*first, customer* second,int incr,bool check){
			if(first==second||!first||!second) return;
			if(check){
				if(incr==1){
				customer* prev1 = first->kan;
				customer* next2 = second->next;

				if (prev1) {
					prev1->next=second;
					second->kan=prev1;
				} else {
					wait = second;
					second->kan=nullptr;
				};

				if (next2) {
					next2->kan = first;
					first->next = next2;
				}
				else{
					wait_tail=first;
					first->next=nullptr;
				}
				second->next=first;
				first->kan=second;
			}
			else{
				customer* prev1 = first->kan;
				customer* next1 = first->next;
				customer* prev2 = second->kan;
				customer* next2 = second->next;
						
				if (prev1) {
					prev1->next = second;
					second->kan = prev1;
				} else {
					wait = second;
					second->kan=nullptr;
				}

				if (prev2) {
					prev2->next = first;
					first->kan = prev2;
				} else {
					wait = first;
				}

				if (next1) {
					next1->kan = second;
					second->next = next1;
				}
				else{
					wait_tail=second;
				}

				if (next2) {
					next2->kan = first;
					first->next = next2;
				}
				else{
					wait_tail=first;
					first->next=nullptr;
				}
			}
			}
			else{
				if(second->next==first){
					customer* prev2= second->kan;
					prev2->next=first;
					first->kan=prev2;
					second->next=first->next;
					second->next->kan=second;
					first->next=second;
					second->kan=first;
				}
				else if(second->kan==first){
					customer* prev1= first->kan;
					prev1->next=second;
					second->kan=prev1;
					first->next=second->next;
					first->next->kan=first;
					second->next=first;
					first->kan=second;
				}
				else{
					customer* prev1 = first->kan;
					customer* next1 = first->next;
					customer* prev2 = second->kan;
					customer* next2 = second->next;
					if (prev1) {
						prev1->next = second;
						second->kan = prev1;
					}

					if (prev2) {
						prev2->next = first;
						first->kan = prev2;
					} 

					if (next1) {
						next1->kan = second;
						second->next = next1;
					}
					
					if (next2) {
						next2->kan = first;
						first->next = next2;
					}
				}
			}			
		}
		void inssort2(customer *head, int n, int incr,int & num) {
			if(head==nullptr) return;
			if(n==1) return;
			customer* sort=head;
			customer* temp_sort=head;;
			for(int i=0;i<incr;++i){
				sort=sort->next;
			};

			for (int i=incr; i<n; i++){
				if(!sort) break;
				temp_sort=sort;
				customer* check=sort->next;
				customer* res=sort;
				int j=i;
				while(j>=0||i==j){
					customer* save=temp_sort->kan;
					if((j%incr)==i%incr) res=temp_sort;
					if((j%incr)==i%incr&&abs(res->energy)<=abs(sort->energy)) {
						if(abs(res->energy)<abs(sort->energy)){
							swap_custormer(res,sort,incr,1);
							num++;
						}
						else if(res->prev->energy>sort->prev->energy){
							swap_custormer(res,sort,incr,1);
							num++;
						}
					}
					if((j%incr)==i%incr&&abs(res->energy)>abs(sort->energy)&&i!=j) 
						break;
					temp_sort=save;
					--j;
				};
				sort=check;
			}
		}

		void ShellShort(customer* head,int num,int& n){
			for(int i=num/2;i>0;i/=2){
				if(i<=2) i=1;
				inssort2(head,num,i,n);
				head=wait;
			};
		}
		void PURPLE()
		{
			if(num_wait==0) return;
			customer* temp_w=wait;
			int num=1;
			int index=1;
			int max=abs(wait->energy);
			for(int i=0;i<num_wait;++i){
				if(abs(temp_w->energy)>= max){
					max=abs(temp_w->energy);
					index=i+1;
				}
				num++;
				temp_w=temp_w->next;
			}
			int n=0;
			ShellShort(this->wait,index,n);
			if(num_wait==0) sum_cus=0;
			BLUE(n % MAXSIZE);
		}
		void REVERSAL(){ 
			if(num_cus==0) return;
			customer* temp2=temp;
			customer* left=temp;
			customer* right=temp->next;
			while(left!=right){
				while(left->energy*temp->energy<0&&left!=right){
					left=left->kan;
				}
				while(right->energy*temp->energy<0&&left!=right){
					right=right->next;
				}
				if(left==right) break;
				else if(left->energy*temp->energy>0&&right->energy*temp->energy>0){
					if(left->next==right||left->kan==right)
						swap_custormer(left,right,1,0);
					else swap_custormer(left,right,2,0);
					if(left==temp) temp2=right;
					customer* temp_temp=right;
					if(left->next==right) break;
					right=left->next;
					left=temp_temp->kan;
				}
			}
			left=temp2;
			right=temp2->next;
			while(left!=right){
				while(left->energy*temp->energy>0&&left!=right){
					left=left->kan;
				}
				while(right->energy*temp->energy>0&&left!=right){
					right=right->next;
				}
				if(left==right) break;
				else if(left->energy*temp->energy<0&&right->energy*temp->energy<0){
					if(left->next==right)
						swap_custormer(left,right,1,0);
					else swap_custormer(left,right,2,0);
					customer* temp_temp=right;
					if(left->next==right) break;
					right=left->next;
					left=temp_temp->kan;
				}
			}

		};

		void helper(customer* head, customer*& save,int& sum,customer*& save_first,customer*& res,int& num_sub){
			if(num_cus<4) return;
			customer* current=head;
			customer* res_temp=head;
			bool check=false;
			int sum_temp=0;
			for(int i=0;i<num_cus;++i){
				if(res_temp->energy>current->energy) res_temp=current;
				sum_temp+=current->energy;
				if((i>=3&&sum_temp<sum)||(i>=3&&sum_temp==sum&&num_sub<=i)){
					if(!check) res=res_temp;
						check=true;
					sum=sum_temp;
					num_sub=i;
					save=current;
					if(res_temp->energy>current->energy) res_temp=current;
					if(res_temp->energy<res->energy) res=res_temp;
					save_first=head;
				}
				current=current->next;
			};
		}
		void UNLIMITED_VOID()
		{
			if(num_cus<4) return;
			customer* current=temp;
			customer* save_cus=nullptr;
			customer* save_first=temp;
			customer* res=nullptr;
			customer* res_temp=current;
			int num_sub=0;
			int sum=0;
			int save=current->energy;
			for(int i=0;i<num_cus;++i){
				if(res_temp->energy>current->energy) res_temp=current;
				sum+=current->energy;
				if(i==3){
					save=sum;
					save_cus=current;
					if(res_temp->energy>current->energy) res_temp=current;
					res=res_temp;
				}
				else if(i>3){
					if(sum<=save){
						save=sum;
						num_sub=i;
						save_cus=current;
						if(res_temp->energy>current->energy) res_temp=current;
						if(res_temp->energy<res->energy) res=res_temp;
					}
				}
				current=current->next;
			};
			current=current->next;
			int n=num_cus;
			for(int i=1;i<n;++i){
				helper(current,save_cus,save,save_first,res,num_sub);
				current=current->next;
			};
			res_temp=res;
			if(num_cus==4){
				for(int i=0;i<num_cus;++i){
					res_temp->print();
					res_temp=res_temp->next;
				};
				return;
			}

			while(res_temp!=save_cus){
				res_temp->print();
				res_temp=res_temp->next;
			}
			if(save_cus){
				save_cus->print();
			}
			while(save_first!=res){
				save_first->print();
				save_first=save_first->next;
			}
		}
		void DOMAIN_EXPANSION()
		{
			int jjk=0;
			int all=0;
			customer* temp_head=head;
			
			while(temp_head){
				if(temp_head->energy>0)
					jjk+=temp_head->energy;
				else
				all+=temp_head->energy;
				temp_head=temp_head->next;
			}
			if(jjk>= abs(all)){
				customer* temp_head=head;

				while(temp_head){
					if (temp_head != nullptr&&temp_head->prev->name=="desk"&&temp_head->kan->next->energy<0){
						customer* temp_temp=temp_head->kan->next;
						temp=temp_temp->energy>0?temp_temp->next:temp_temp->kan;
						temp_temp->next->kan=temp_temp->kan;
						temp_temp->kan->next=temp_temp->next;
						delete temp_temp;
						num_cus--;
						temp_head->kan=nullptr;
						if(num_cus==0){
							temp=nullptr;
						}
					}
					if(temp_head!=nullptr&&temp_head->prev->name=="wait"&&((!temp_head->kan&&wait->energy<0)||(temp_head->kan&&temp_head->kan->next->energy<0))){
						customer* temp_wait= (temp_head->kan)? temp_head->kan->next:wait;
						if(temp_wait==wait){
							wait=wait->next;
							if(wait) wait->kan=nullptr;
							temp_wait->kan=nullptr;
							num_wait--;
							if(num_wait==0){
								wait=nullptr;
								wait_tail=nullptr;
							}
						}
						else{
							temp_wait->kan->next=temp_wait->next;
							if(temp_wait->next) temp_wait->next->kan=temp_wait->kan;
							else{
								wait_tail=temp_wait->kan;
							}
							temp_wait->kan=nullptr;
							num_wait--;
							if(num_wait==0){
								wait=nullptr;
								wait_tail=nullptr;
							}
						}
					}
					temp_head=temp_head->next;
				};
				temp_head=tail_order;
				while(temp_head){
					customer* save_node=temp_head->kan2;
					if(temp_head->energy<0){
						temp_head->print();
						if(temp_head->kan2){
							temp_head->kan2->next=temp_head->next;
							if(temp_head->next){
								temp_head->next->kan2=temp_head->kan2;
							}
							else tail_order=temp_head->kan2;
						}
						else{
							if(temp_head->next){
								head=temp_head->next;
								temp_head->next->kan2=nullptr;
							}
							else {
								head=nullptr;
								tail_order=nullptr;
								sum_cus=0;
							}
						};
						delete temp_head->prev;
						delete temp_head;
					}
					temp_head=save_node;
				}
			}
			else{
				customer* temp_head=head;

				while(temp_head){
					if (temp_head != nullptr&&temp_head->prev->name=="desk"&&temp_head->kan->next->energy>0){
						customer* temp_temp=temp_head->kan->next;
						temp=temp_temp->energy>0?temp_temp->next:temp_temp->kan;
						temp_temp->next->kan=temp_temp->kan;
						temp_temp->kan->next=temp_temp->next;
						delete temp_temp;
						num_cus--;
						temp_head->kan=nullptr;
						if(num_cus==0){
							temp=nullptr;
						}
					}
					if(temp_head!=nullptr&&temp_head->prev->name=="wait"&&((!temp_head->kan&&wait->energy>0)||(temp_head->kan&&temp_head->kan->next->energy>0))){
						customer* temp_wait= (temp_head->kan)? temp_head->kan->next:wait;
						if(temp_wait==wait){
							wait=wait->next;
							if(wait) wait->kan=nullptr;
							temp_wait->kan=nullptr;
							num_wait--;
							if(num_wait==0){
								wait=nullptr;
								wait_tail=nullptr;
							}
						}
						else{
							temp_wait->kan->next=temp_wait->next;
							if(temp_wait->next) temp_wait->next->kan=temp_wait->kan;
							else{
								wait_tail=temp_wait->kan;
							}
							temp_wait->kan=nullptr;
							num_wait--;
							if(num_wait==0){
								wait=nullptr;
								wait_tail=nullptr;
							}
						}
					}
					temp_head=temp_head->next;
				};
				temp_head=tail_order;
				while(temp_head){
					customer* save_node=temp_head->kan2;
					if(temp_head->energy>0){
						temp_head->print();
						if(temp_head->kan2){
							temp_head->kan2->next=temp_head->next;
							if(temp_head->next){
								temp_head->next->kan2=temp_head->kan2;
							}
							else tail_order=temp_head->kan2;
						}
						else{
							if(temp_head->next){
								head=temp_head->next;
								temp_head->next->kan2=nullptr;
							}
							else {
								head=nullptr;
								tail_order=nullptr;
								sum_cus=0;
							}
						};
						delete temp_head->prev;
						delete temp_head;
					};
					temp_head=save_node;
				}
			};
			addWaitCus();
		}
		void LIGHT(int num)
		{
			customer* temp2=temp;
			if(num>0){
				for(int i=0;i<num_cus;++i){
					temp2->print();
					temp2=temp2->next;
				};
			}
			else if(num<0){
				for(int i=num_cus;i>0;--i){
					temp2->print();
					temp2=temp2->kan;
				}
			}
			else{
				temp2=wait;
				for(int i=0;i<num_wait;++i){
					temp2->print();
					temp2=temp2->next;
				}
			}
		}
		
};
