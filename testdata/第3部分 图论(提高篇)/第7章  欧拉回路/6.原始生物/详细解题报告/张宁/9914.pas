const inp='pie.in';
      out='pie.out';
var c,v:array[1..1000] of integer;
    w,u:array[1..1000] of boolean;
    min:longint;
    i,j,n:longint;
    l,r,a,b,cn:integer;
    cd:array[1..1000] of longint;
function find(i:integer):integer;
begin
 if i<>c[i] then
  c[i]:=find(c[i]);
 find:=c[i];
end;
begin
 assign(input,inp);reset(input);
 readln(n);
 for i:=1 to 1000 do begin
  c[i]:=i;v[i]:=0;cd[i]:=0;
  w[i]:=false;u[i]:=false;
 end;
 for i:=1 to n do begin
  readln(l,r);
  w[l]:=true;w[r]:=true;
  a:=find(l);b:=find(r);
  if a<>b then c[a]:=b;
  dec(v[l]);inc(v[r]);
 end;
 close(input);
 min:=n;
 for i:=1 to 1000 do
  if w[i] then begin
   cn:=find(i);u[cn]:=true;
   if v[i]>0 then
    inc(cd[cn],v[i])
  end;
 for i:=1 to 1000 do
  if u[i] then begin
   if cd[i]=0 then cd[i]:=1;
   inc(min,cd[i])
  end;
 assign(output,out);rewrite(output);
 writeln(min);
 close(output)
end.