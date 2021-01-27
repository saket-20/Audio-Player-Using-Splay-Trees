# Audio-Player-Using-Splay-Trees
a music player with autocomplete feature for song names and a splay tree data structure for storing addresses of the songs along with names for efficient retrieval

An audio player is implemented with an autocomplete(suggestion) feature for partially typed song
names and addresses of the songs are efficiently stored in the memory using splay tree.
Splay tree was chosen for storing and retrieving memory locations given the names of the songs
because usually people are likely to want to listen to only a few songs repeatedly out of all the songs
available.
Trie is chosen for implementing the Autocomplete feature, all data in the nodes under the last matching
node will be printed to suggest songs beginning with the given prefix
