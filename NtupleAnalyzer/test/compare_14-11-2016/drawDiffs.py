from ROOT import *

def main():
    fs = []
    ts = []
    h0s = []
    h1s = []
    hs = []
    cs = []
    vs = ["event", "pT", "Eta", "Phi", "EpdgIDcharge", "miniIso", "miniIsoCharged", "miniIsoNeutral", "jetPtRel", "jetCSV", "jetPtRatio", "sip3D", "dxy", "dz", "segmentCompatibility"]
    labels = ["muons", "electrons", "taus", "jets"]
    fs.append(TFile.Open("test_muons_ND/f_"+labels[0]+".root"))
    ts.append(fs[-1].Get("t"))
    #xmin = []
    #xmax = []
    #for i,v in enumerate(vs):
    #    print v, (t.GetMinimum(v+"_0"), t.GetMaximum(v+"_0"), t.GetMinimum(v+"_1"), t.GetMaximum(v+"_1"))
    #    xmin.append(min(t.GetMinimum(v+"_0"), t.GetMinimum(v+"_1")))
    #    xmax.append(max(t.GetMaximum(v+"_0"), t.GetMaximum(v+"_1")))
    for i,v in enumerate(vs):
        #t.Draw(">>elist", "diffs["+str(i)+"]==1")
        #tel = TEventList(gDirectory.Get("elist"))
        #t.SetEventList(tel)
        #print v, (t.GetMinimum(v+"_0"), t.GetMaximum(v+"_0"), t.GetMinimum(v+"_1"), t.GetMaximum(v+"_1"))
        #continue
        cs.append(TCanvas())
        t.Draw("diffs["+str(i)+"]>>hd_"+str(i))
        #print "diffs["+str(i)+"]>>hd"+str(i), v, (globals()["hd"+str(i)]).GetMean()
        if globals()["hd_"+str(i)].GetMean() != 0:
            xmin = min(t.GetMinimum(v+"_0"), t.GetMinimum(v+"_1"))
            xmax = max(t.GetMaximum(v+"_0"), t.GetMaximum(v+"_1"))
            cs.append(TCanvas(v+"_0", v+"_0"))
            t.Draw(v+"_0>>h_"+str(v)+"_0(100,"+str(xmin)+","+str(xmax)+")", "diffs["+str(i)+"]==1")
            #t.Draw(v+"_0>>h"+str(v)+"_0")
            cs.append(TCanvas(v+"_1", v+"_1"))
            t.Draw(v+"_1>>h_"+str(v)+"_1(100,"+str(xmin)+","+str(xmax)+")", "diffs["+str(i)+"]==1")
            #t.Draw(v+"_1>>h"+str(v)+"_1")
            h0s.append(globals()["h_"+str(v)+"_0"])
            h1s.append(globals()["h_"+str(v)+"_1"])
            h0s[-1].SetLineWidth(1)
            h0s[-1].SetLineColor(2)
            h1s[-1].SetLineWidth(3)
            h1s[-1].SetLineColor(1)
            cs.append(TCanvas(v, v))
            hs.append(THStack("h_"+str(v), ""))
            #hs[-1].Add(h0s[-1])
            hs[-1].Add(h1s[-1])
            hs[-1].Add(h0s[-1])
            hs[-1].Draw("nostack")

    raw_input("Press enter to continue...")

if __name__ == "__main__":
    main()
