#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"ran2.c"
#define L 1000
float expd(void);
long sd=-933176683;

main()
{
  int i,j,k,count2,iw,count,n,NRUN=1,t,TMAX=4000,ii,jj,ni,nj,id,xl,yl,M=7,tt,flag,ratio,RELAX=1200,counti,countj,delta,idelta,inorm,nr,a,limit,before1,before2,after,*flip,count0,count1;
  float sum,r,p,mu,*op,tot_sum,*s_op,*time_avg,zero,tot_flip,tot_zero,*norm,*prob_del,total_factor=0.,tot_op,new_sum,*per,*per1,*thr,*dist,*dist_m,*dist_b,*money,*savings,epsi,trade,*bitcoin,price,alpha,I,total_transaction,total_bitcoin,r_ii,r_jj,T,E1,E2,p1,p2,trade1,trade2,w,q;
  float transaction_series[30],avg_trn,bar;
  int m,num,t1,t2;
  float tau = 4000.0;
FILE *fpt;


fpt = fopen("MyFile2.csv", "w+");

fprintf(fpt,"Time, I, Bit coin,Price\n");


 ////////////////////////////can change NRUN depending on run-time


//  ratio=L/M;
 //   norm=(float *)calloc(LARGE, sizeof(float));
//  prob_del=(float *)calloc(LARGE, sizeof(float));
  
//  fpt3=fopen("elec_clg_list_3","r");
//  fpt1=fopen("mag_L30_p0.12n","w");
//  fpt2=fopen("flip_prob_L30_p0.12n","w");
 
///////   p=0.5;

     money = (float *)calloc(L, sizeof(float));

     bitcoin= (float *)calloc(L, sizeof(float));
    
     savings = (float *)calloc(L,sizeof(float));
    
       dist = (float *)calloc(TMAX,sizeof(float));
     dist_m = (float *)calloc(TMAX,sizeof(float));
     dist_b = (float *)calloc(TMAX,sizeof(float));

     thr =(float *)calloc(L,sizeof(float));

//     s_op=(float *)calloc(TMAX,sizeof(float));
//     time_avg=(float *)calloc(TMAX,sizeof(float));
//     per=(float *)calloc(TMAX,sizeof(float));

//     per0=(float *)calloc(TMAX,sizeof(float));
//     per1=(float *)calloc(TMAX,sizeof(float));
 //    super_spin = (int **)calloc(M,sizeof(int*));


//  for(i=0;i<51;i++) {fscanf(fpt3,"%d %d\n",&clg_list[i],&a); }

  
//  limit=50;




  bar=0.;       /// trading bias

  q=0.2;        //fraction of people owning bitcoin initially



  for(i=0;i<TMAX;i++) {dist_m[i]=0; dist_b[i]=0; dist[i]=0;}
 

   alpha=6;

  for(n=0;n<NRUN;n++)
  {
 
     for(i=0;i<30;i++) {transaction_series[i]=-1;}

     total_bitcoin=0; 

     for(i=0;i<L;i++)
     {
       
        money[i]=ran2(&sd)/L; if(ran2(&sd)<q) {bitcoin[i]=(1./q)*ran2(&sd)/L;} else {bitcoin[i]=0;} total_bitcoin+=bitcoin[i];
        savings[i]=ran2(&sd);
      //  thr[i]=10*ran2(&sd);
       
     }   

 //    bitcoin[L/2]=10;
     
     price=1;   //initial price of bitcoin
     
     for(t=0;t<TMAX;t++)
     {

         total_transaction=0;      total_bitcoin=0;

       //   price=1;

         for(j=0;j<L;j++) {total_bitcoin+=bitcoin[j];}

         for(j=0;j<L;j++)
         {
            ii=ran2(&sd)*L; jj=ran2(&sd)*L;

        //    epsi=ran2(&sd);

        //    r_ii=price*bitcoin[ii]/money[ii];  r_jj=price*bitcoin[jj]/money[jj];


            E1=(money[ii]-price*bitcoin[ii])/(money[ii]+price*bitcoin[ii]);
            E2=(money[jj]-price*bitcoin[jj])/(money[jj]+price*bitcoin[jj]);


        //    p1=exp(-1*E1/T); p2=exp(-1*E2/T);

            if(E1>0 && E2<bar) {num=1;} 
            else if(E1<bar && E2>0) {num=2;}
            else if(E1<bar && E2<bar)  {if(ran2(&sd)<1) {num=3;} else { if(ran2(&sd)<0.5) { num=2;} else {num=1;}}}
            else {num=0;}

//            if(t1==0 && t2==1) {num=2;}
  //          else if(t1==1 && t2==0) {num=1;}
    //        else {num=0;}
      //   if(num>0) {   printf("%d\n",num);}


if(num > 0 && ran2(&sd) <1 - (t/tau)){
num = 0 ; 
}


          switch(num)
          {

            case 0:

           trade=(1-savings[ii])*money[ii]+(1-savings[jj])*money[jj];

           epsi=ran2(&sd);

           money[ii]=money[ii]*savings[ii]+epsi*trade;
           money[jj]=money[jj]*savings[jj]+(1-epsi)*trade;



            break; 

            case 3:
              

           trade=(1-savings[ii])*bitcoin[ii]+(1-savings[jj])*bitcoin[jj];

           epsi=ran2(&sd);

           bitcoin[ii]=bitcoin[ii]*savings[ii]+epsi*trade;
           bitcoin[jj]=bitcoin[jj]*savings[jj]+(1-epsi)*trade;


             total_transaction+=trade;

            break;
            case 1:
  
               trade1=(1-savings[ii])*money[ii];
               trade2=(1-savings[jj])*bitcoin[jj];

               if(trade1>price*trade2)
               {
                  money[ii]=savings[ii]*money[ii]+trade1-price*trade2;
                  bitcoin[ii]=bitcoin[ii]+trade2;

                  money[jj]=money[jj]+price*trade2;
                  bitcoin[jj]=savings[jj]*bitcoin[jj];

                  total_transaction+=trade2;
               }          
               else
               {
                  money[ii]=savings[ii]*money[ii];
                  bitcoin[ii]=bitcoin[ii]+trade1/price;

                  money[jj]=money[jj]+trade1;
                  bitcoin[jj]=savings[jj]*bitcoin[jj]+trade2-trade1/price;

                  total_transaction+=trade1/price;
               }

               
            
            break;

            case 2:
            
               trade1=(1-savings[ii])*bitcoin[ii];
               trade2=(1-savings[jj])*money[jj];


              

               if(trade2>trade1*price)
               {
                  money[jj]=savings[jj]*money[jj]+trade2-price*trade1;
                  bitcoin[jj]=bitcoin[jj]+trade1;

                  money[ii]=money[ii]+price*trade1;
                  bitcoin[ii]=savings[ii]*bitcoin[ii];

                  total_transaction+=trade1;                 

               }
               else
               {
                  money[jj]=savings[jj]*money[jj];
                  bitcoin[jj]=bitcoin[jj]+trade2/price;

                  money[ii]=money[ii]+trade2;
                  bitcoin[ii]=savings[ii]*bitcoin[ii]+trade1-trade2/price;

                  total_transaction+=trade2/price;
               }


            //   total_transaction+=trade;

            
             break;
            

            }

          
     
          
         }

           I=total_transaction/total_bitcoin;

            flag=0;

            for(i=0;i<30;i++)
            {
               if(transaction_series[i]==-1) {transaction_series[i]=I; flag=1;}

            }
            if(flag==0)
            {

                for(i=0;i<29;i++) { transaction_series[i]=transaction_series[i+1];}
                transaction_series[29]=I;

            }

            avg_trn=0;
            for(i=0;i<30;i++)
            {

               avg_trn+=transaction_series[i];

            }
 
            avg_trn=avg_trn/30;

           if(I>0){ price=alpha/(I+0.0);}
           else {price=0;}

 
           fprintf(fpt,"%d, %f, %f, %f\n",t,I,price,total_bitcoin);           ////////////////time (col1) vs price (col3)



       
       if(t>RELAX)
       {

         for(i=0;i<L;i++)
         {
 
            m=money[i]*1000;
            if(m<TMAX) {dist_m[m]++;}

            m=price*bitcoin[i]*1000;
            if(m<TMAX) {dist_b[m]++;}

            w=money[i]+price*bitcoin[i];             

            m=w*1000;
 
           if(m<TMAX) {dist[m]++;}   

         }

       }



    
     }
//end of time loop

    

//  tot_flip+=(float)flag;
  


  }
//end of realisation


   
  for(i=0;i<TMAX;i++)
  {

  //   printf("%d %f %f %f\n",i,dist[i],dist_m[i],dist_b[i]);           /////////////////////// wealth distribution
 
  }


}

fclose(fp);

float expd(void)
{

   float lam, x,y,z;
  
   lam=0.01; 

   z=ran2(&sd);
   x=log(1-z)/(-1*lam);
 
   return(x);
}







