# CS-300-lzw


In this assignment you will implement an algorithm for data compression. The
purpose of data compression is to take a file A and, within a reasonable amount of
time, transform it into another file B in such a way that: (i) B is smaller than A, and
(ii) it is possible to reconstruct A from B. A program that converts A into B is called
a compressor, and one that undoes this operation is called an uncompressor. Popular
programs such as WinZip perform this function, among others. Compressing data
enables us to store data more efficiently on our storage devices or transmit data faster
using communication facilities since fewer bits are needed to represent the actual
data.
Of course, a compressor cannot guarantee that the file B will always be smaller than
A. It is easy to see why: if this were possible, then imagine what would happen if you
just kept iterating the method, compressing the output of the compressor. In fact, with
a little bit of thinking, you should be able to convince yourself that any compressor
that compresses some files must also actually enlarge some files. (Understand why
this should be the case!) Nevertheless, compressors tend to work pretty well on the
kinds of files that are typically found on computers, and they are widely used in
practice. 
