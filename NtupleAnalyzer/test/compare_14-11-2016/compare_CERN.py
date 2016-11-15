from ROOT import *

import sys

def checkIfMerged(vals):
    if True:
        if vals[0].count('.') > 0:
            v = vals[0]
            vals[0] = v[:6]
            vals.insert(1, v[6:])
            #print vals
    #if True:
    #    for j,v in enumerate(vals):
    #        if v.count('.') == 2:
    #            if vals[j][0] != '-':
    #                vals[j] = v[:7]
    #                vals.insert(j+1, v[7:])
    #            else:
    #                vals[j] = v[:8]
    #                vals.insert(j+1, v[8:])
    if True:
        for j,v in enumerate(vals):
            if v.count('.') == 2:
                #print v
                #print v.find('.')
                #print v[:v.find('.')+5]
                #print v[v.find('.')+6:]
                vals[j] = v[:v.find('.')+5]
                vals.insert(j+1, v[v.find('.')+6:])

class PhysicsObject:
    def __init__(self, l, sf="lepton"):
        self.l = ' '.join(l.split())
        #print self.l
        vals = self.l.split(" ")
        checkIfMerged(vals)
        self.props = []
        if sf == "lepton":
            self.props.append(("evt", "%10d", int(vals[len(self.props)])))
            self.props.append(("pt", "%10.5f", float(vals[len(self.props)])))
            self.props.append(("eta", "%10.5f", float(vals[len(self.props)])))
            self.props.append(("phi", "%10.5f", float(vals[len(self.props)])))
            self.props.append(("E", "%10.5f", float(vals[len(self.props)])))
        elif sf == "jet":
            self.props.append(("evt", "%6d", int(vals[len(self.props)])))
            self.props.append(("pt", "%10.5f", float(vals[len(self.props)])))
            self.props.append(("eta", "%10.5f", float(vals[len(self.props)])))
            self.props.append(("phi", "%10.5f", float(vals[len(self.props)])))
            self.props.append(("E", "%10.5f", float(vals[len(self.props)])))
        elif sf == "tau":
            self.props.append(("evt", "%6d", int(vals[len(self.props)])))
            self.props.append(("pt", "%10.5f", float(vals[len(self.props)])))
            self.props.append(("eta", "%10.5f", float(vals[len(self.props)])))
            self.props.append(("phi", "%10.5f", float(vals[len(self.props)])))
            self.props.append(("E", "%10.5f", float(vals[len(self.props)])))

    def getPrintString(self):
        '''
        %10d%10.5f%10.5f%10.5f%10.5f%5d%5d%15.5f%15.5f%15.5f%10.5f%10.5f%10.5f%10.5f%10.5f%10.5f%21.5f
        '''
        s = ""
        for p in self.props:
            s += (" "+(p[1] % p[2]))
        return s
    
    def getParameter(self, name):
        ret = None
        for p in self.props:
            if p[0] == name:
                ret = p
                break
        return ret

    def getParVal(self, name):
        ret = None
        for p in self.props:
            if p[0] == name:
                ret = p[2]
                break
        return ret

class Lepton(PhysicsObject):
    def __init__(self, l):
        PhysicsObject.__init__(self, l, sf="lepton")
        vals = self.l.split(" ")
        #print vals
        checkIfMerged(vals)
        self.props.append(("pdgId", "%5d", int(vals[len(self.props)])))
        self.props.append(("charge", "%5d", int(vals[len(self.props)])))

        self.props.append(("miniRelIso", "%15.5f", float(vals[len(self.props)])))
        #self.props.append(("miniRelIsoCharged", "%15.5f", float(vals[len(self.props)])))
        self.props.append(("miniIsoCharged", "%15.5f", float(vals[len(self.props)])))
        #self.props.append(("miniRelIsoNeutral", "%15.5f", float(vals[len(self.props)])))
        self.props.append(("miniIsoNeutral", "%15.5f", float(vals[len(self.props)])))
        self.props.append(("jetPtRel", "%10.5f", float(vals[len(self.props)])))
        self.props.append(("jetCSV", "%10.5f", float(vals[len(self.props)])))
        self.props.append(("jetPtRatio", "%10.5f", float(vals[len(self.props)])))
        self.props.append(("sip3d", "%10.5f", float(vals[len(self.props)])))
        self.props.append(("dxy", "%10.5f", float(vals[len(self.props)])))
        self.props.append(("dz", "%10.5f", float(vals[len(self.props)])))

class Jet(PhysicsObject):
    def __init__(self, l):
        PhysicsObject.__init__(self, l, sf="jet")
        vals = self.l.split(" ")
        #print vals
        checkIfMerged(vals)
        self.props.append(("CSVv2", "%10.5f", float(vals[len(self.props)])))
        self.props.append(("MET pt", "%10.5f", float(vals[len(self.props)])))
        self.props.append(("MET phi", "%10.5f", float(vals[len(self.props)])))

class Tau(PhysicsObject):
    def __init__(self, l):
        PhysicsObject.__init__(self, l, sf="tau")
        vals = self.l.split(" ")
        #print vals
        checkIfMerged(vals)
        self.props.append(("dxy", "%10.5f", float(vals[len(self.props)])))
        self.props.append(("dz", "%10.5f", float(vals[len(self.props)])))
        self.props.append(("decayModeFinding", "%10.5f", float(vals[len(self.props)])))
        self.props.append(("byLooseCombinedIsolationDeltaBetaCorr3Hits", "%10.5f", float(vals[len(self.props)])))

class Electron(Lepton):
    def __init__(self, l):
        Lepton.__init__(self, l)
        vals = self.l.split(" ")
        #print vals
        checkIfMerged(vals)
        self.props.append(("eleMVA", "%21.5f", float(vals[len(self.props)])))

class Muon(Lepton):
    def __init__(self, l):
        Lepton.__init__(self, l)
        vals = self.l.split(" ")
        #print vals
        checkIfMerged(vals)
        self.props.append(("segmentCompatibility", "%21.5f", float(vals[len(self.props)])))

def main(argv):
    roundingErr = 0.01
    with open(argv[1]) as f1:
        content1 = f1.readlines()
    with open(argv[2]) as f2:
        content2 = f2.readlines()
    objs1 = []
    objs2 = []
    if argv[0] == "electrons":
        for l in content1[1:]:
            objs1.append(Electron(l))
        for l in content2[1:]:
            objs2.append(Electron(l))
    elif argv[0] == "muons":
        for l in content1[1:]:
            objs1.append(Muon(l))
        for l in content2[1:]:
            objs2.append(Muon(l))
    elif argv[0] == "jets":
        for l in content1[1:]:
            objs1.append(Jet(l))
        for l in content2[1:]:
            objs2.append(Jet(l))
    elif argv[0] == "taus":
        for l in content1[1:]:
            objs1.append(Tau(l))
        for l in content2[1:]:
            objs2.append(Tau(l))
    evts1 = set([o.getParVal("evt") for o in objs1])
    evts2 = set([o.getParVal("evt") for o in objs2])
    ex1 = sorted(list(evts1-evts2))
    ex2 = sorted(list(evts2-evts1))
    ies = sorted(list(evts1.intersection(evts2)))
    print
    #print "<: ", ex1
    #print ">: ", ex2
    #print "=: ", ies

    if argv[0] == "muons":
        print "MUONS"
#        print "absolute dxy, dz diffs skipped"
#        print "jetPtRel rounding diffs skipped"
#        print "jetPtRatio rounding diffs skipped"
        print "all rounding diffs skipped"
#        print "jetCSV == -10.0 vs. jetCSV == 0.0 skipped"
        #print "skip jetCSV comparing"
        #print "E rounding diffs skipped"
        #print "skip jetPtRel comparing"
#        print "skipp all miniIsoNeutral(0.0, < 0.0) diffs"
#        print "miniIsoNeutral rounding diffs skipped"
        print "<: ", ex1
        print ">: ", ex2
        print "=: ", ies
        iesl = list(ies[:int(argv[3])]) if (int(argv[3]) != -1) else ies
        for i in iesl:
            ps1 = [o for o in objs1 if o.getParVal("evt") == i][0]
            ps2 = [o for o in objs2 if o.getParVal("evt") == i][0]
    #        if len(ps1) > 1 or len(ps2) > 1:
    #            sys.exit()
            dprsn = str(i)+" ["
            for p in xrange(0, len(ps1.props)):
                if ps1.props[p] != ps2.props[p]:
                    if False:
                        continue
#                    elif (ps1.props[p][0] in ["dxy", "dz"]) and abs(ps1.props[p][2]) == abs(ps2.props[p][2]): # absolute dxy, dz diffs skipped
#                        continue
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # jetPtRel rounding diffs skipped
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2]<0.02 if ps1.props[p][2] != 0.0 else False): # jetPtRel rounding diffs skipped
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # jetPtRel rounding diffs skipped
#                        continue
#                    elif (ps1.props[p][0] in ["jetPtRatio"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # jetPtRatio rounding diffs skipped
#                        continue
                    elif (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # all rounding diffs skipped
                        continue
#                    elif (ps1.props[p][0] in ["jetCSV"]) and (ps1.props[p][2] == -10.0) and (ps2.props[p][2] == 0.0): # jetCSV == -10.0 vs. jetCSV == 0.0 skipped
#                        continue
                    #elif (ps1.props[p][0] in ["jetCSV"]) and (ps1.props[p][2] == -99.0) and (ps2.props[p][2] == 0.0): # jetCSV == -99.0 vs. jetCSV == 0.0 skipped
                    #    continue
                    #elif (ps1.props[p][0] in ["jetCSV"]): # skip jetCSV comparing for muons
                    #    continue
                    #elif (ps1.props[p][0] in ["jetPtRel"]): # skip jetPtRel comparing
                    #    continue
                    #elif (ps1.props[p][0] in ["E"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # E rounding diffs skipped
                    #    continue
                    #elif (ps1.props[p][0] in ["eleMVA"]):
                    #    print ps1.props[p], ps2.props[p]
                    #    sys.exit()
                    #    continue
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and (ps1.props[p][2] == 0.0 and ps2.props[p][2] < 0): # skipp all miniIsoNeutral(0.0, < 0.0) diffs
#                        continue
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # miniIsoNeutral rounding diffs skipped
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # miniIsoNeutral rounding diffs skipped
#                        continue
                    else:
                        #dprsn += " "+ps1.props[p][0]
                        dprsn += " "+ps1.props[p][0]+"("+((ps1.props[p][1]) % (ps1.props[p][2])).replace(" ", "")+", "+((ps2.props[p][1]) % (ps2.props[p][2])).replace(" ", "")+")"
            dprsn += " ]"
            #print ps1[0].getPrintString()
            #print ps2[0].getPrintString()
            #print
            print dprsn

    elif argv[0] == "electrons":
        print "ELECTRONS"
#        print "absolute dxy, dz diffs skipped"
#        print "jetPtRel rounding diffs skipped"
#        print "jetPtRatio rounding diffs skipped"
        print "all rounding diffs skipped"
#        print "skip jetCSV comparing"
        #print "E rounding diffs skipped"
#        print "skipp all miniIsoNeutral(0.0, < 0.0) diffs"
#        print "miniIsoNeutral rounding diffs skipped"
        print "<: ", ex1
        print ">: ", ex2
        print "=: ", ies
        iesl = list(ies[:int(argv[3])]) if (int(argv[3]) != -1) else ies
        for i in iesl:
            ps1 = [o for o in objs1 if o.getParVal("evt") == i][0]
            ps2 = [o for o in objs2 if o.getParVal("evt") == i][0]
    #        if len(ps1) > 1 or len(ps2) > 1:
    #            sys.exit()
            dprsn = str(i)+" ["
            for p in xrange(0, len(ps1.props)):
                if ps1.props[p] != ps2.props[p]:
                    if False:
                        continue
#                    elif (ps1.props[p][0] in ["dxy", "dz"]) and abs(ps1.props[p][2]) == abs(ps2.props[p][2]): # absolute dxy, dz diffs skipped
#                        continue
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # jetPtRel rounding diffs skipped
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2]<0.02 if ps1.props[p][2] != 0.0 else False): # jetPtRel rounding diffs skipped
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # jetPtRel rounding diffs skipped
#                        continue
#                    elif (ps1.props[p][0] in ["jetPtRatio"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # jetPtRatio rounding diffs skipped
#                        continue
                    elif (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # all rounding diffs skipped
                        continue
#                    elif (ps1.props[p][0] in ["jetCSV"]): # skip jetCSV comparing
#                        continue
                    #elif (ps1.props[p][0] in ["eleMVA"]):
                    #    print ps1.props[p], ps2.props[p]
                    #    sys.exit()
                    #    continue
                    #elif (ps1.props[p][0] in ["E"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # E rounding diffs skipped
                    #    continue
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and (ps1.props[p][2] == 0.0 and ps2.props[p][2] < 0): # skipp all miniIsoNeutral(0.0, < 0.0) diffs
#                        continue
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # miniIsoNeutral rounding diffs skipped
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # miniIsoNeutral rounding diffs skipped
#                        continue
                    else:
                        #dprsn += " "+ps1.props[p][0]
                        dprsn += " "+ps1.props[p][0]+"("+((ps1.props[p][1]) % (ps1.props[p][2])).replace(" ", "")+", "+((ps2.props[p][1]) % (ps2.props[p][2])).replace(" ", "")+")"
            dprsn += " ]"
            #print ps1[0].getPrintString()
            #print ps2[0].getPrintString()
            #print
            print dprsn

    elif argv[0] == "jets":
        print "JETS"
        print "all rounding diffs skipped"
        print "<: ", ex1
        print ">: ", ex2
        print "=: ", ies
        iesl = list(ies[:int(argv[3])]) if (int(argv[3]) != -1) else ies
        for i in iesl:
            ps1 = [o for o in objs1 if o.getParVal("evt") == i][0]
            ps2 = [o for o in objs2 if o.getParVal("evt") == i][0]
    #        if len(ps1) > 1 or len(ps2) > 1:
    #            sys.exit()
            dprsn = str(i)+" ["
            for p in xrange(0, len(ps1.props)):
                if ps1.props[p] != ps2.props[p]:
                    if False:
                        continue
                    elif (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # all rounding diffs skipped
                        continue
#                    elif (ps1.props[p][0] in ["dxy", "dz"]) and abs(ps1.props[p][2]) == abs(ps2.props[p][2]): # absolute dxy, dz diffs skipped
#                        continue
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # jetPtRel rounding diffs skipped
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2]<0.02 if ps1.props[p][2] != 0.0 else False): # jetPtRel rounding diffs skipped
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # jetPtRel rounding diffs skipped
#                        continue
#                    elif (ps1.props[p][0] in ["jetPtRatio"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # jetPtRatio rounding diffs skipped
#                        continue
#                    elif (ps1.props[p][0] in ["jetCSV"]): # skip jetCSV comparing
#                        continue
                    #elif (ps1.props[p][0] in ["eleMVA"]):
                    #    print ps1.props[p], ps2.props[p]
                    #    sys.exit()
                    #    continue
                    #elif (ps1.props[p][0] in ["E"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # E rounding diffs skipped
                    #    continue
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and (ps1.props[p][2] == 0.0 and ps2.props[p][2] < 0): # skipp all miniIsoNeutral(0.0, < 0.0) diffs
#                        continue
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # miniIsoNeutral rounding diffs skipped
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # miniIsoNeutral rounding diffs skipped
#                        continue
                    else:
                        #dprsn += " "+ps1.props[p][0]
                        dprsn += " "+ps1.props[p][0]+"("+((ps1.props[p][1]) % (ps1.props[p][2])).replace(" ", "")+", "+((ps2.props[p][1]) % (ps2.props[p][2])).replace(" ", "")+")"
            dprsn += " ]"
            #print ps1[0].getPrintString()
            #print ps2[0].getPrintString()
            #print
            print dprsn
    elif argv[0] == "taus":
        print "TAUS"
        print "all rounding diffs skipped"
        print "<: ", ex1
        print ">: ", ex2
        print "=: ", ies
        iesl = list(ies[:int(argv[3])]) if (int(argv[3]) != -1) else ies
        for i in iesl:
            ps1 = [o for o in objs1 if o.getParVal("evt") == i][0]
            ps2 = [o for o in objs2 if o.getParVal("evt") == i][0]
    #        if len(ps1) > 1 or len(ps2) > 1:
    #            sys.exit()
            dprsn = str(i)+" ["
            for p in xrange(0, len(ps1.props)):
                if ps1.props[p] != ps2.props[p]:
                    if False:
                        continue
                    elif (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # all rounding diffs skipped
                        continue
#                    elif (ps1.props[p][0] in ["dxy", "dz"]) and abs(ps1.props[p][2]) == abs(ps2.props[p][2]): # absolute dxy, dz diffs skipped
#                        continue
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # jetPtRel rounding diffs skipped
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2]<0.02 if ps1.props[p][2] != 0.0 else False): # jetPtRel rounding diffs skipped
#                    elif (ps1.props[p][0] in ["jetPtRel"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # jetPtRel rounding diffs skipped
#                        continue
#                    elif (ps1.props[p][0] in ["jetPtRatio"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # jetPtRatio rounding diffs skipped
#                        continue
#                    elif (ps1.props[p][0] in ["jetCSV"]): # skip jetCSV comparing
#                        continue
                    #elif (ps1.props[p][0] in ["eleMVA"]):
                    #    print ps1.props[p], ps2.props[p]
                    #    sys.exit()
                    #    continue
                    #elif (ps1.props[p][0] in ["E"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # E rounding diffs skipped
                    #    continue
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and (ps1.props[p][2] == 0.0 and ps2.props[p][2] < 0): # skipp all miniIsoNeutral(0.0, < 0.0) diffs
#                        continue
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and round(ps1.props[p][2], 2) == round(ps2.props[p][2], 2): # miniIsoNeutral rounding diffs skipped
#                    elif (ps1.props[p][0] in ["miniIsoNeutral"]) and (abs(ps1.props[p][2]-ps2.props[p][2])/ps1.props[p][2] < roundingErr if ps1.props[p][2] != 0.0 else False): # miniIsoNeutral rounding diffs skipped
#                        continue
                    else:
                        #dprsn += " "+ps1.props[p][0]
                        dprsn += " "+ps1.props[p][0]+"("+((ps1.props[p][1]) % (ps1.props[p][2])).replace(" ", "")+", "+((ps2.props[p][1]) % (ps2.props[p][2])).replace(" ", "")+")"
            dprsn += " ]"
            #print ps1[0].getPrintString()
            #print ps2[0].getPrintString()
            #print
            print dprsn

    #print list(set(evts1).intersection(evts2))

if __name__ == "__main__":
    main(sys.argv[1:])

