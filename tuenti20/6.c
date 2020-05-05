#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>   //inet_addr
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];
char outBuffer[BUFFER_SIZE];

int x = 0, y = 0;
int px = 256, py = -256;
char lb[256][256];

typedef struct P {
    int x, y;
} P;

const P DMOVES[8] = {
    {-2, -1},
    {-2, +1},
    {-1, -2},
    {-1, +2},
    {+1, -2},
    {+1, +2},
    {+2, -1},
    {+2, +1}
};

const char MOVES_STR[8][5] = {
    "2l1u", "2l1d", "1l2u", "1l2d",
    "1r2u", "1r2d", "2r1u", "2r1d"
};

const char* moveStr(int dx, int dy)
{
    for(int i =0; i < 8; i++)
        if(DMOVES[i].x == dx && DMOVES[i].y == dy)
            return MOVES_STR[i];
    assert(0);
    return "";
}

void printLb()
{
    FILE* f = fopen("debug.txt", "w");
    for(int i = 0; i < 256; i++)
        fprintf(f, "%.256s\n", &lb[i][0]);
    fclose(f);
}

void feedInfo(const char* buffer)
{
    int i = 0;
    for(int yy = -2; yy <= 2; yy++)
    {
        for(int xx = -2; xx <= 2; xx++)
        {
            char c = buffer[i];
            if(c == 'P') {
                px = x + xx;
                py = y + yy;
                c = 'P';
            }
            else if(c == 'K') {
                c == '.';
            }
            lb[128+y+yy][128+x+xx] = c;
            i++;
        }
        i++;
    }
    if(0)
        printLb();
}

const int MAX_COST = 9999999;
const char* nextMove()
{
    static P q[2048];
    static int cost[256][256];
    static P from[256][256];
    // try to find path to 'P'
    for(int i = 0; i < 256; i++)
    for(int j = 0; j < 256; j++)
        cost[i][j] = MAX_COST;
    int qBeg = 0;
    int qEnd = 1;
    q[qBeg] = (P){x, y};
    cost[128+y][128+x] = 0;
    P firstNotExplored = {256, 256};
    while(qEnd - qBeg)
    {
        P ori = q[qBeg];
        qBeg = (qBeg + 1) % 2048;
        for(int mi = 0; mi < 8; mi++)
        {
            const P dm = DMOVES[mi];
            const P dest = {ori.x+dm.x, ori.y+dm.y};
            const int pCost = cost[128+ori.y][128+ori.x];
            const int destCost = cost[128+dest.y][128+dest.x];
            const char c = lb[128+dest.y][128+dest.x];
            if(c == 'P') {
                from[128+dest.y][128+dest.x] = ori;
                P b = dest;
                while(from[128+b.y][128+b.x].x != x || from[128+b.y][128+b.x].y != y)
                    b = from[128+b.y][128+b.x];
                const P dd = {b.x - x, b.y - y};
                x = b.x;
                y = b.y;
                return moveStr(dd.x, dd.y);
            }
            if(c == '.') {
                if(pCost + 1 < destCost) {
                    cost[128+dest.y][128+dest.x] = pCost + 1;
                    from[128+dest.y][128+dest.x] = ori;
                    q[qEnd] = dest;
                    qEnd = (qEnd + 1) % 2048;
                }
            }
            if(c == ' ') {
                if(firstNotExplored.x == 256) {
                    firstNotExplored = ori;
                    if(px == 256)
                        goto end;
                }
            }
        }
    }
end:
    assert(firstNotExplored.x != 256);
    P b = firstNotExplored;
    while(from[128+b.y][128+b.x].x != x || from[128+b.y][128+b.x].y != y)
        b = from[128+b.y][128+b.x];
        const P dd = {b.x - x, b.y - y};
        x = b.x;
        y = b.y;
        return moveStr(dd.x, dd.y);
}

int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
        
    server.sin_addr.s_addr = inet_addr("52.49.91.111");
    server.sin_family = AF_INET;
    server.sin_port = htons( 2003 );

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected");

    x = y = 0;
    px = py = 256;
    memset(lb, ' ', 256*256);

    int debugPrint = 0;
    while(1)
    {
        int numRecv = recv(socket_desc, buffer, BUFFER_SIZE-1, 0);
        if( numRecv >= 0)
        {
            buffer[numRecv] = '\0';
            if(debugPrint)
                printf("%s\n", buffer);
            if(x == px && y == py) {
                if(!debugPrint)
                    printf("%s\n", buffer);
                printLb();
                break;
            }
            feedInfo(buffer);
        }
        else {
            printf("error recv: %d\n", numRecv);
        }
        
        int interactiveMode = 0;
        int pressEnterToContinue = 0;
        if(interactiveMode)
        {
            fgets(outBuffer, BUFFER_SIZE, stdin);
            write(socket_desc, outBuffer, strlen(outBuffer));
        }
        else {
            if(pressEnterToContinue)
                getchar();
            const char* moveStr = nextMove();
            if(debugPrint)
                printf("Send move: %s\n", moveStr);
            write(socket_desc, moveStr, strlen(moveStr));
        }

    }
    
    return 0;
}
