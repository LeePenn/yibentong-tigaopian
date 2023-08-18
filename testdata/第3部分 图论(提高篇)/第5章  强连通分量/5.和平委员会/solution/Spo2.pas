{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q-,R-,S+,T-,V+,X+,Y+}
{$M 65520,0,655360}
program spo;
const
     inf='spo.in';
     ouf='spo.out';
type
    link=^node;
    node =record
            x:integer;next:link;
          end;
    tv=array[1..16000]of shortint;
    tarr=array[1..16000]of link;
var
   a:Tarr;
   n:integer;

procedure init;
var
   i,m,u,v:integer;
   r:link;
begin
     readln(n,m);
     for i:=1 to n*2 do
      begin
           new(a[i]);
           a[i]^.next:=nil;
      end;
     for i:=1 to m do
     begin
           readln(u,v);
           new(r);
           r^.x:=v;r^.next:=a[u]^.next;
           a[u]^.next:=r;
           new(r);
           r^.x:=u;r^.next:=a[v]^.next;
           a[v]^.next:=r;
     end;
end;

procedure main;
var
   i,j,fp,rp:integer;
   v:array[1..16000]of integer;
   q:array[1..8000]of integer;
   flag:boolean;
   r:link;
begin
     fillchar(v,sizeof(v),0);
     for i:=1 to n do
     if (v[i+i-1]=1) or (v[i+i]=1) then
     else
     begin
          flag:=true;
          fillchar(q,sizeof(q),0);fp:=1;rp:=1; q[1]:=i+i-1;
          v[i+i-1]:=1;
          repeat
                r:=a[q[fp]]^.next;
                while r<>nil do
                 begin
                       if v[r^.x]=1 then
                       begin flag:=false; break end;
                       if odd(r^.x) then
                          begin
                             if v[r^.x+1]<>1 then
                             begin
                                  v[r^.x+1]:=1;
                                  inc(rp);
                                  q[rp]:=r^.x+1
                             end;
                          end else
                          begin
                             if v[r^.x-1]<>1 then
                             begin
                                  v[r^.x-1]:=1;
                                  inc(rp);
                                  q[rp]:=r^.x-1
                             end;
                          end;
                      r:=r^.next;
                 end;
                if not flag then break;
                inc(fp);
          until fp>rp;
          if flag then continue;
          for j:=1 to rp do v[q[j]]:=0;

          fillchar(q,sizeof(q),0);fp:=1;rp:=1; q[1]:=i+i;
          v[i+i]:=1;
          repeat
                r:=a[q[fp]]^.next;
                while r<>nil do
                 begin
                      if v[r^.x]=1 then
                       begin writeln('NIE'); exit end;
                       if odd(r^.x) then
                       begin
                             if v[r^.x+1]<>1 then
                             begin
                                  v[r^.x+1]:=1;
                                  inc(rp);
                                  q[rp]:=r^.x+1
                             end
                       end else
                       begin
                             if v[r^.x-1]<>1 then
                             begin
                                  v[r^.x-1]:=1;
                                  inc(rp);
                                  q[rp]:=r^.x-1
                             end;
                       end;
                      r:=r^.next;
                 end;
                inc(fp);
          until fp>rp;
     end;

     for i:=1 to n*2 do if v[i]=1 then writeln(i);
end;

begin
     assign(input,inf);reset(input);
     assign(output,ouf);rewrite(output);
     init;
     main;
     close(input);close(output);
end.