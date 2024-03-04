CFLAGS = -Wall

all: bfs dfs def bruteforce tremaux bellmanford wallfollower

bfs:
	gcc $(CFLAGS) BFS.c wczytywanie_z_pliku.c -o bfs.out

dfs:
	gcc $(CFLAGS) DFS.c -o dfs.out

def:
	gcc $(CFLAGS) DEF.c wczytywanie_z_pliku.c -o def.out

bruteforce:
	gcc $(CFLAGS) Bruteforce.c -o bruteforce.out

tremaux:
	gcc $(CFLAGS) Tremaux.c -o tremaux.out

bellmanford:
	gcc $(CFLAGS) Bellman-ford.c wczytywanie_z_pliku.c -o bellmanford.out

wallfollower:
	gcc $(CFLAGS) Wall-follower.c wczytywanie_z_pliku.c -o wallfollower.out

clean:
	rm -f bfs.out dfs.out def.out bruteforce.out tremaux.out bellmanford.out wallfollower.out