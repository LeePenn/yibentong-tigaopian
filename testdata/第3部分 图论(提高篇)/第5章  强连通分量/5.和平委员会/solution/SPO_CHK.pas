program SPO_CHK;
const
    maxn=16000;
type
    TLink=^TNode;
    TNode=record
        v:longint;
        next:TLink;
    end;
var
    g:array[1..maxn] of TLink;
    vis:array[1..maxn] of boolean;
    n,m:longint;

procedure insert(x,y:longint);
var
    s:TLink;
begin
    new(s); s^.v:=y; s^.next:=g[x]^.next; g[x]^.next:=s;
end;

procedure print_errmsg;
begin
    writeln('Wrong!');
    close(input);
    halt;
end;

procedure init;
var
    i,j,k:longint;
    s:string;
begin
    s:=paramstr(0);
    for i:=length(s) downto 1 do
        if s[i]='\' then begin
            delete(s,1,i);
            break;
        end;
    if paramcount<>3 then begin
        writeln('Usage: ',s,' InputFile OutputFile StdOutFile');
        halt;
    end;
    assign(input,paramstr(1));reset(input);
    readln(n,m);
    for i:=1 to 2*n do begin
        new(g[i]);
        g[i]^.next:=nil;
    end;
    for i:=1 to m do begin
        readln(j,k);
        insert(j,k);insert(k,j);
    end;
    close(input);
end;

procedure check;
var
    i,j:longint;
    st:string;
    s:TLink;
begin
    assign(input,paramstr(2));reset(input);
    for i:=1 to n do begin
        {$I-}
        readln(j);
        {$I+}
        if ioresult<>0 then begin
            close(input);
            assign(input,paramstr(2));reset(input);
            readln(st); if st<>'NIE' then print_errmsg;
            close(input);
            assign(input,paramstr(3));reset(input);
            readln(st); if st<>'NIE' then print_errmsg;
            close(input);
            writeln('Right!');
            halt;
        end;

        if (j+1) div 2<>i then print_errmsg;
        vis[j]:=true;
        s:=g[j]^.next;
        while s<>nil do begin
            if vis[s^.v] then print_errmsg;
            s:=s^.next;
        end;
    end;
    writeln('Right!');
end;

begin
    init;
    check;
    close(input);
end.
