uses dos;
var
  f:text;
  c:array[1..1000,1..1000] of longint;
  min,max,t:longint;
  a,b,n,i,j,k,x,y,p,q:integer;
  h,fe,m,m1:word;
  o:char;
 begin
  for o:='0' to '9' do
   begin
{  gettime(h,fe,m,m1);
  writeln(h,':',fe,':',m,':',m1);}
  assign(f,'square.in'+o);
  reset(f);
  readln(f,a,b,n);
  for i:=1 to a do
     begin
       for j:=1 to b do read(f,c[i,j]);
       readln(f);
     end;
   close(f);
  t:=1000000000;
  for i:=1 to a-n+1 do
    for j:=1 to b-n+1 do
      begin
        min:=1000000000;
        max:=0;
        for x:=0 to n-1 do
          for y:=0 to n-1 do
            begin
              if c[x+i,j+y]>max then max:=c[x+i,y+j];
              if c[x+i,y+j]<min then min:=c[x+i,y+j];
            end;
        if max-min<t then begin t:=max-min;p:=i;q:=j;end;
      end;
  writeln(t:20,p:10,q:4,o:9,a:5,b:5,n:5);
  assign(f,'square.ou'+o);
  rewrite(f);
  writeln(f,t);
  close(f);
 { gettime(h,fe,m,m1);
  writeln(h,':',fe,':',m,':',m1);}
 end;
end.
