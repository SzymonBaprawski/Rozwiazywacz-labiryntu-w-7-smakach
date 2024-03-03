CFLAGS = -Wall

all: bfs dfs def bruteforce tremaux bellmanford wallfollower

bfs:
	gcc $(CFLAGS) bfs.c -o bfs.out

dfs:
	gcc $(CFLAGS) dfs.c -o dfs.out

def:
	gcc $(CFLAGS) def.c wczytywanie_z_pliku.c -o def.out

bruteforce:
	gcc $(CFLAGS) bruteforce.c -o bruteforce.out

tremaux:
	gcc $(CFLAGS) tremaux.c -o tremaux.out

bellmanford:
	gcc $(CFLAGS) bellmanford.c wczytywanie_z_pliku.c -o bellmanford.out

wallfollower:
	gcc $(CFLAGS) Wall-follower.c wczytywanie_z_pliku.c -o wallfollower.out

clean:
	rm -f bfs.out dfs.out def.out bruteforce.out tremaux.out bellmanford.out wallfollower.out