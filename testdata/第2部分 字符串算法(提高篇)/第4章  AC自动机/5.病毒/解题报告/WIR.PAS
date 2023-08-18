{$A+,B-,D-,E-,F-,G+,I-,L-,N+,O-,P-,Q-,R-,S-,T-,V+,X+,Y-}
{$M 65520,0,655360}
{Problem: Poland OI #7 1999/2000, Stage I, Viruses}
{Author: Zig}
program __program_wir;
const
  InputFileName='wir.in';
  OutputFileName='wir.out';
const
  maxl=30000;
type
  PIntArr=^TIntArr;
  TIntArr=array [1..maxl+1] of integer;
  PByteArr=^TByteArr;
  TByteArr=array [1..maxl+1] of byte;
  PBoolArr=^TBoolArr;
  TBoolArr=array [1..maxl+1] of boolean;
var
  son,sig:array [0..1] of PIntArr; { $son$ is son of the nodes, and
   $sig$ is the TRUE graph after merging as well as deleting the nodes, but should be coloring in fact}
  danger:PBoolArr; {the same as described in the solution}
procedure make_tree;
var
  ch:char;
  i,j,n,p,q,sc:integer;
begin {of sub-routie make_tree}
  read(n);
  if not seekeof then;
  sc:=1;
  for i:=1 to n do
  begin
    p:=1;
    while not seekeoln do
    begin
      read(ch); {input}
      q:=ord(ch)-ord('0');
      if son[q]^[p]=0 then {build binary search tree according to the inputs}
      begin
        inc(sc);
        son[q]^[p]:=sc;
      end;
      p:=son[q]^[p];
    end;
    danger^[p]:=true;
    readln;
  end;
end; {of sub-routine make_tree}
procedure make_sig;
var
  q:TIntArr;
  op,cl,t,i,j:integer;
begin {of sub-routine make_sig}
  q[1]:=1;
  sig[0]^[1]:=1;
  sig[1]^[1]:=1;
  op:=1;cl:=0;
  repeat
    inc(cl);
    if not danger^[q[cl]] then
     for i:=0 to 1 do
      if son[i]^[q[cl]]<>0 then
      begin
        t:=sig[i]^[q[cl]];
        sig[i]^[q[cl]]:=son[i]^[q[cl]];
        if danger^[t] then danger^[son[i]^[q[cl]]]:=true; {iterative procedure to get the values of $danger$}
        for j:=0 to 1 do
         if son[j]^[t]<>0 then sig[j]^[son[i]^[q[cl]]]:=son[j]^[t]  {merge the nodes}
                          else sig[j]^[son[i]^[q[cl]]]:=sig[j]^[t]; {we do not delete nodes in fact,
                                        we only color them as DANGER for that's easier}
        inc(op);q[op]:=son[i]^[q[cl]];
      end;
  until cl>=op;
end; {of sub-routine make_sig}
function find_circle:boolean;
var
  stack:TIntArr;
  sp,s,i:integer;
  c:PByteArr;
  v:PBoolArr;
begin {of sub-routine find_circle}
  find_circle:=true;new(c);new(v);
  fillchar(c^,sizeof(c^),0);
  fillchar(v^,sizeof(v^),false);
  sp:=1;stack[1]:=1;
  v^[1]:=true;
  while sp>0 do {do a depth-first search to find circles}
  begin
    s:=stack[sp];dec(sp);
    if c^[s]>1 then v^[s]:=false else
    begin
      v^[s]:=true;
      i:=c^[s];inc(c^[s]);
      inc(sp);stack[sp]:=s;
      if not danger^[sig[i]^[s]] then
       if v^[sig[i]^[s]] then
       begin
         dispose(c);
         dispose(v);
         exit;
       end else
       begin
         inc(sp);
         stack[sp]:=sig[i]^[s];
       end;
    end;
  end;
  find_circle:=false;dispose(c);dispose(v);
end; {of sub-routine find_circle}
begin {of the main program}
  assign(input,InputFileName);
  assign(output,OutputFileName);
  reset(input);rewrite(output);
  new(son[0]);new(son[1]);
  new(sig[0]);new(sig[1]);
  new(danger);
  fillchar(son[0]^,sizeof(son[0]^),0);
  fillchar(son[1]^,sizeof(son[1]^),0);
  fillchar(sig[0]^,sizeof(sig[0]^),0);
  fillchar(sig[1]^,sizeof(sig[1]^),0);
  fillchar(danger^,sizeof(danger^),false); {above are initializations}
  make_tree; {input data}
  make_sig; {make graph}
  dispose(son[0]);dispose(son[1]);
  if find_circle then writeln('TAK') else writeln('NIE'); {output the answer}
  dispose(sig[0]);dispose(sig[1]);
  dispose(danger); {finalizations}
  close(input);close(output);
end. {of the main program}