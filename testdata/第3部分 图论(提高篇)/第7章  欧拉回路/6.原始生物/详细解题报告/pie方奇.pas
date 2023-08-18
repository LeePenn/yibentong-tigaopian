Program Pie_9914;
const maxn=1000;
type tp=array[1..maxn] of integer;
var c,d,mark:tp;
    i,j,x,y,n,ans:longint;
    f1,f2:text;

procedure init;
begin
  assign(f1,'pie.in');
  reset(f1);
  assign(f2,'pie.out');
  rewrite(f2);
end;

procedure Link;
var i,k1,k2,t1,t2:integer;
    l1,l2:tp;
begin
  k1:=x;t1:=0;
  while c[k1]>0 do
  begin
    inc(t1);l1[t1]:=k1;
    k1:=c[k1];
  end;

  k2:=y;t2:=0;
  while c[k2]>0 do
  begin
    inc(t2);l2[t2]:=k2;
    k2:=c[k2];
  end;

  if k1<>k2 then c[k2]:=k1;
  for i:=1 to t1 do l1[i]:=k1;
  for i:=1 to t2 do l2[i]:=k1;
end;

procedure main;
begin
  readln(f1,n);
  fillchar(c,sizeof(c),0);
  fillchar(d,sizeof(d),0);
  fillchar(mark,sizeof(mark),0);
  for i:=1 to n do
  begin
    readln(f1,x,y);
    mark[x]:=1;mark[y]:=1;
    inc(d[x]);dec(d[y]);
    Link;
  end;

  ans:=n;
  for i:=1 to 1000 do
  if mark[i]=1 then
  begin
    j:=i;
    while c[j]>0 do j:=c[j];
    if c[j]=0 then
    begin
      inc(ans);
      c[j]:=-1;
    end;
    if d[i]>0 then
    begin
      if c[j]=-1 then
      begin
        dec(ans);
        c[j]:=-2;
      end;
      inc(ans,d[i]);
    end;
  end;

  writeln(f2,ans);
  close(f2);
end;

begin
  init;
  main;
end.