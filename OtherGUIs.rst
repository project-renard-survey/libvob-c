=========================
Other graphical libraries
=========================


Graphical primitive libs
************************

OpenGL
======

OpenGL provides primitives for any kind of drawing but best it is
known of painting triangles. This is something that I'll be using with
libvob implementation.


Cairo
=====

I like cairo. It's not that fast with python but I can live with it.


X11
===

X is not drawing library in sense but it's very fundamental part of
current systems, even at some times I wonder why. For instance for
embedded stuff it takes a bit too much energy to move pixmaps from
client to server and then from server to kernel space.

There are actually many ways to separate drawing operations from one
single process (well we have X in the end). The best known is the
client-server separation but X window may be embedded within another
application and thus provide application-application separation.

http://standards.freedesktop.org/xembed-spec/xembed-spec-latest.html

The process separation shall be taken into consideration. It's very
important part of robustness provided by the underlying operation
system.


Widget libraries
****************

AWT (Java)
==========

I like the simple Graphics interface :) Unfortunately the interface is
not "3D" and AWT is a bit unstable and slow.


Enlightenment
=============

This is one that I have newer used. From the documents I have read
that it uses relational positioning. It's quite fast as well. I have
read some raster's code and it was so ugly and long for a small
application that I started to think "no thank you".

The documentation is also a bit of pain to jump in as everything is
named with eesomething and they just make no sense to me. EWL, ETK,
EVAS, blaa, blaa


SWT (Java)
==========

Layouting
---------

I have done several times a layout which was supposed to be 10 minutes
of work but I used 4 hours instead. I just cannot get the "model" of it.
I always tend to use GridLayout because it's closest to TeX's boxes.


Thread protectionism
--------------------

The UI code is so hard to understand after a while. The problem lies
in the thread safety and sequential control flow processing. When you
want to develop user interface with multiple threads it comes
nightmare to understand what's actually going on as you don't know it.
For example::

    button's click handler {

        createUser(model, "foo");

	model.listUsers().get(0).doSomething();

    }

The problem was that createUser was usually called by other thread,
and to get SWT's needed thread safety, createUser had it wrapped with
asynchronic hand-over to GUI thread.::

    Display.getDefault().async(new Runnable(){
        public void run() {
             actuallyCreateUser(...);
	}
    });

Now I needed to make huge fix to the code::

    button's click handler {

        createUser(model, "foo");

        Display.getDefault().async(new Runnable(){
            public void run() {
                model.listUsers().get(0).doSomething();
	    }
        });
    }

...to get the code be executed _later_. These can not be seen from the
code and they are quite hard to debug as your code makes no sense at
first. I usually place printouts for debugging purposes and debug
would just say that "nothing created".

I think the actual problem in this case is that native code shall not
be called with another thread context but this is *definitely not same
as* concurrent data access.


JFace views
-----------

JFace views are too abstract and they depend too heavily on SWT native
interfaces.


Swing (Java)
============

Swing looks like its design - it's abstract. Sorting in table was
much more harder than in SWT. Has same thread problems as SWT.


GTK+
====

Scoping problems
----------------

GTK+ is pain to write with C. You can not put things in the scope with
your callback. Well you do can put one parameter but it's not typed
and checked by compiler. For multiple parameters, e.g. two parameters,
you can make a struct and put that as a parameter (who deletes that
data?), or use global variable (ugly), or put the things into widgets'
object hashtable. I think the last one is closest for the best answer.

Nested functions
----------------

As there are no nested functions all callback are distributed
around. Yeks!  Not good for reading the code.


Qt
==

Widgets
-------

Widgets have a tender to grow in sense of functions as do GTK+ widgets
too. It's a problem of C++ perhaps.

I found it pitty that there are method to:

- addWidget

- addLayout

- addItem

while those do pretty much same thing: add X to Y.


Layouting
---------

Layouting in Qt is nicely done as it uses boxes and streches. That
applies also for GTK+ though. 


Minor things
------------

I have tried QtCreator but it's not that good. Eclipse is just way
better for Java editing. Let me re-issue this after I get used to the
editor.

Second thing is that compiling takes ages. I had a small three source
file project and it just takes forewer to start.

Also I hate that I can not have small main in the UI file as it makes
it very easy to start some window fast. This rant was for using Qt one
day.


QML
===

Qml was a nice, new kind of toolkit. Animations were totally
re-thought. Instead of writing animations to move x and y of an item,
you can say whenever x changes (same for y) you use specific
animation. Now every change to x and y is actually animated. Of course
you could use specific setter to make immeadiate translation.

This is something what I need to think of. Previous libvob used one
kind of animation for all animations. I need to re-evaluate if this is
good thing after all. In practise the developer would need to say to
matcher if different animation is wanted. Or there could be specific
lob for that.
