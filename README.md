# OpenLinkList
This is a link list that is free and open for public use. It supports two forms of access, index and cursor/pointer access.
The index method simply iterates through the list
The cursor/pointer method relies on the user to iterate through the list. 
Both methods can be used at the same time.

This Link List does NOT store indexes so it will become slow with huge lists if you are not accessing data sequentially. 

///////////////////// NOTES \\\\\\\\\\\\\\\\\\\\
Be carful when you add data, the cursor may not move how you expect it to, make sure to check its location with getCurrentIndex() when you need to know where you are.

