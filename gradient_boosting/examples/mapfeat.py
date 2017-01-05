#!/usr/bin/python
import sys

fo = open( 'reg.txt', 'w' ) 
cnt = 6
fmap = {}
for l in open( 'reg.data' ):
    arr = l.split(',')
    fo.write(arr[8])
    for i in xrange( 0,6 ):
        fo.write( ' %d:%s' %(i,arr[i+2]) )
    
    if arr[0] not in fmap:
        fmap[arr[0]] = cnt
        cnt += 1
    
    fo.write( ' %d:1' % fmap[arr[0]] )	
    fo.write('\n')

fo.close()

# create feature map for machine data
fo = open('featmap.txt', 'w')
# list from machine.names
names = ['vendor','MYCT', 'MMIN', 'MMAX', 'CACH', 'CHMIN', 'CHMAX', 'PRP', 'ERP' ]; 

for i in xrange(0,6):
    fo.write( '%d\t%s\tint\n' % (i, names[i+1]))

for v, k in sorted( fmap.iteritems(), key = lambda x:x[1] ):
    fo.write( '%d\tvendor=%s\ti\n' % (k, v))
fo.close()
