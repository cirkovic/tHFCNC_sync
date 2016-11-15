from ROOT import *
from array import array
import random

cs = []
hs = []
ts = []
fs = []

def newTree(brs):
    fs.append(TFile.Open("f"+str(len(fs))+".root", "RECREATE"))
    ts.append(TTree("t"+str(len(ts)), "t"+str(len(ts))))
    for b in brs:
        if len(b) <= 2:
            print b[0], b[1], b[0]+"/"+str(b[1].typecode).upper()
            ts[-1].Branch(b[0], b[1], b[0]+"/"+str(b[1].typecode).upper())
        else:
            print b[0], b[1], b[2]
            ts[-1].Branch(b[0], b[1], b[2])

def main():
    d = {}
    d['evt'] = array('i', [0])
    d['sr'] = array('d', [0.0])
    d['nvr'] = array('i', [0])
    d['vr'] = array('d', [0.0]*10)
    newTree([("evt", d['evt']), ("sr", d['sr']), ("nvr", d['nvr']), ("vr", d['vr'], "vr[nvr]/D")])
    for i in xrange(0,10000):
        d['evt'][0] = i
        d['sr'][0] = random.random()
        d['nvr'][0] = int((4*random.random()))
        for j in xrange(0, d['nvr'][0]):
            d['vr'][j] = random.gauss(0.5, 1)
        for t in ts:
            t.SetName("tree")
            t.Fill()
    for t in ts:
        t.Write()
    #cs.append(TCanvas())
    #ts[-1].Draw("evt")
    #cs.append(TCanvas())
    #ts[-1].Draw("sr")
    for f in fs:
        f.Close()
    
if __name__ == "__main__":
    main()
    raw_input("Pess enter to continue...")

