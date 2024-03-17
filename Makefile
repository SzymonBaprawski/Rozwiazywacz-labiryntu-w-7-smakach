CFLAGS = -Wall

all: bfs def bellmanford wallfollower astar bfsopt

bfs:
	gcc $(CFLAGS) BFS.c wczytywanie_z_pliku.c -o bfs.out

bfsopt:
	gcc $(CFLAGS) BFSoptymalizowany.c wczytywanie_z_pliku.c -o bfsopt.out
	
def:
	gcc $(CFLAGS) DEF.c wczytywanie_z_pliku.c -o def.out

bellmanford:
	gcc $(CFLAGS) Bellman-ford.c wczytywanie_z_pliku.c -o bellmanford.out

wallfollower:
	gcc $(CFLAGS) Wall-follower.c wczytywanie_z_pliku.c -o wallfollower.out

astar:
	gcc $(CFLAGS) astar.c wczytywanie_z_pliku.c -o astar.out -lm

clean:
	rm -f bfs.out dfs.out def.out bruteforce.out tremaux.out bellmanford.out wallfollower.out astar.out