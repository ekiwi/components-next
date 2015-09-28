# Components Next
Some experiments with loosely coupled components on microcontrollers.

Basically I'm working on improving the [xpcc components](https://github.com/roboterclubaachen/xpcc/tree/develop/src/xpcc/communication/xpcc).

The main ideas for improvement are:
* use futures (the concept, not necessarily the std implementation) instead
  of callbacks for return values from remote procedures
* use a generic list implementation in the dispatcher, or at least move
  the specific list implementation out of the dispatcher code and test
* see if we can avoid using the xpcc smart pointer, as it adds runtime
  as well as memory overhead by requiring a separate allocation
* make system more robust, it should be able to handle multiple messages
  of the same type as well as source and destination without leaking memory
  (not sure if this could happen now, but I was told it could..)
* use a new component structure, loosely based on the one described in the
  [nesC paper](http://www.tinyos.net/papers/nesc.pdf)
	* one file format describes our custom data types (enums, structs, etc.)
	  as well as interfaces using these types
	* every component gets exactly one xml file that describes the
	  the interfaces it provides
	* another xml describes the whole project, it defines the containers
	  (i.e. boards or sometimes CAN interfaces) as well as component
	  instances that are assigned unique ids on a project basis
* optimize calls to components available on the same container to be
  basically a simple function call (plus one or two runtime checks and
  some packing/unpacking)
	* this might allow us to drop the use of static shared memory location
	  making our components more reusable
* make it possible to use several CAN adapters controlled by one executable
	* since now, not all containers can be reached with a single CAN message,
	  we need routing
* investigate a "more dynamic" loading of components, maybe a lookup table that
  components can insert themselves in once they are ready (this is in order not
  to rely as much on static objects as static CTORs are foobar)
* it might be interesting to have the communication schedule the
  `update` or `run` methods of components
