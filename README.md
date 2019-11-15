Fire-and-Forget (FaF) sending of UDP datagrams from C++ while hiding the complexity of the boost::asio library.

Python has me spoiled, in Python simple things are typically very easy to do. In C++ things are sometimes different, the boost::asio libraries are very powerful networking libraries they can handle all sorts of networking scenarios, but when you want to do a simple thing, like just send a string via UDP things can seem over complicated.

So to hide some of the complexities of boost::asio when I just want to Fire-And-Forget a string via UDP I wrote a wrapper class: **boost_udp_send_faf**

It can send a string or a binary buffer to a specified IP address:

```cpp
#include "boost_udp_send_faf.h"

boost_udp_send_faf("192.168.1.44", 8861).send("The message!");
```
This sends the message to 192.168.1.44 on port 8861.

If your program needs send multiple datagrams, then we can keep the socket open and reuse the end-point like this:

```cpp
#include "boost_udp_send_faf.h"
 
boost_udp_send_faf sender("192.168.1.44", 8861);
	
for (auto i = 0; i != 10; i++) {
    sender.send("Lots of messages! :-/");
}
```

More info can be found [here](https://www.ridgesolutions.ie/index.php/2019/11/15/fire-and-forget-wrapper-for-sending-of-simple-udp-data-using-boostasio-libraries/)
