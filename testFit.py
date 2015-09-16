import math, ROOT

path = "/shome/cheidegg/d/MPAF/workdir/root/FakeRatio/FakeRatio2015Bmu.root"
lep = "Mu"


def prepare(hist, h_data):

	if hist.Integral() > h_data.Integral():
		s = math.floor(h_data.Integral() / hist.Integral() * 100.) / 100.
		#hist.Scale(s)
		print "rounding down by " + str(s)
		return s
	#return hist
	return 1.

def doubleFit(h_data, h_ewk, h_qcd, hmin = 0, hmax = 0):

	if hmin == 0: hmin = h_data.GetXaxis().GetXmin()
	if hmax == 0: hmax = h_data.GetXaxis().GetXmax()
	
	s_ewk = prepare(h_ewk, h_data)
	s_qcd = prepare(h_qcd, h_data)

	#if h_ewk.Integral() + h_qcd.Integral() > h_data.Integral():
	#	s = math.floor( h_data.Integral() / (h_ewk.Integral() + h_qcd.Integral())* 100.) / 100.
	#	h_ewk.Scale(s)
	#	h_qcd.Scale(s)
	#	print "rounding down again by " + str(s)

	x    = ROOT.RooRealVar("x", "x", hmin, hmax)
	alist = ROOT.RooArgList(x)
	rset  = ROOT.RooArgSet (x)

	rdh_data = ROOT.RooDataHist("data", "data", alist, h_data  )
	rdh_ewk  = ROOT.RooDataHist("ewk" , "ewk" , alist, h_ewk   )
	rdh_qcd  = ROOT.RooDataHist("qcd" , "qcd" , alist, h_qcd   )

	pdf_ewk  = ROOT.RooHistPdf("ewk" , "ewk" , rset, rdh_ewk  )
	pdf_qcd  = ROOT.RooHistPdf("qcd" , "qcd" , rset, rdh_qcd  )

	print "defaults are:"
	print "data = " + str(h_data.Integral())
	print "ewk = " + str(h_ewk.Integral() / h_data.Integral()) + " at " + str(h_ewk.Integral())
	print "qcd = " + str(h_qcd.Integral() / h_data.Integral()) + " at " + str(h_qcd.Integral())

	int_data = h_data.Integral(h_data.GetXaxis().FindBin(hmin), h_data.GetXaxis().FindBin(hmax))
	int_ewk  = h_ewk .Integral(h_ewk .GetXaxis().FindBin(hmin), h_ewk .GetXaxis().FindBin(hmax))
	int_qcd  = h_qcd .Integral(h_qcd .GetXaxis().FindBin(hmin), h_qcd .GetXaxis().FindBin(hmax))
	
	rrv_ewk  = ROOT.RooRealVar("ewk" , "ewk" , int_ewk * s_ewk, 0.0         , int_data)
	rrv_qcd  = ROOT.RooRealVar("qcd" , "qcd" , int_qcd * s_qcd, int_data*0.1, int_data)

	pdfs     = ROOT.RooArgList(pdf_ewk, pdf_qcd)
	coeff    = ROOT.RooArgList( rrv_ewk,rrv_qcd)

	totPdf   = ROOT.RooAddPdf("totPdf", "totPdf", pdfs, coeff)
	result   = totPdf.fitTo(rdh_data, ROOT.RooFit.SumW2Error(False), ROOT.RooFit.Extended() ) #, ROOT.RooFit.PrintLevel(-1))
 
	return [rrv_ewk.getVal()/int_ewk, rrv_qcd.getVal()/int_qcd]


def singleFit(h_data, h_mc, hmin = 0, hmax = 0):

	if hmin == 0: hmin = h_data.GetXaxis().GetXmin()
	if hmax == 0: hmax = h_data.GetXaxis().GetXmax()

	x    = ROOT.RooRealVar("x", "x", hmin, hmax)
	alist = ROOT.RooArgList(x)
	rset  = ROOT.RooArgSet (x)

	rdh_data = ROOT.RooDataHist("data", "data", alist, h_data  )
	rdh_mc   = ROOT.RooDataHist("mc"  , "mc"  , alist, h_mc    )

	int_data = h_data.Integral(h_data.GetXaxis().FindBin(hmin), h_data.GetXaxis().FindBin(hmax))
	int_mc   = h_mc  .Integral(h_mc  .GetXaxis().FindBin(hmin), h_mc  .GetXaxis().FindBin(hmax))

	print int_data
	print int_mc

	pdf_mc   = ROOT.RooHistPdf("mc"  , "mc"  , rset  , rdh_mc  )
	rrv_mc   = ROOT.RooRealVar("mc"  , "mc"  , int_data, int_data * 0.8, int_data )

	pdfs     = ROOT.RooArgList(pdf_mc)
	coeff    = ROOT.RooArgList(rrv_mc)

	totPdf   = ROOT.RooAddPdf("totPdf", "totPdf", pdfs, coeff)
	result   = totPdf.fitTo(rdh_data, ROOT.RooFit.SumW2Error(False), ROOT.RooFit.Extended(), ROOT.RooFit.PrintLevel(-1))

	return rrv_mc.getVal() / int_mc





def doPlot(c, h_data, h_ewk, h_qcd, name):

	h_sum = h_ewk.Clone()
	h_sum.Add(h_qcd)

	m = h_data.GetMaximum()
	#m = max(h_sum.GetMaximum(), h_data.GetMaximum())

	h_sum.Draw("hist")
	h_sum.SetFillStyle(1000)
	h_sum.SetFillColor(ROOT.kGray)
	h_sum.SetMaximum(1.25 * m)
	h_qcd.Draw("hist same")
	h_qcd.SetFillStyle(0)
	h_qcd.SetLineColor(ROOT.kBlue)
	h_qcd.SetMaximum(1.25 * m)
	h_ewk.Draw("hist same")
	h_ewk.SetFillStyle(0)
	h_ewk.SetLineColor(ROOT.kRed)
	h_ewk.SetMaximum(1.25 * m)
	h_data.Draw("pe same")
	h_data.SetMarkerStyle(8)
	h_data.SetMarkerSize(1.8)
	h_data.SetMarkerColor(ROOT.kBlack)
	h_data.SetLineColor(ROOT.kBlack)
	h_data.SetMaximum(1.25 * m)
	c.SaveAs(name + ".png")




c = ROOT.TCanvas("c", "c", 975, 600)

f = ROOT.TFile(path, "read")

h_data = f.Get("MR_Num" + lep + "MTinvMET/datacorr")
h_ewk  = f.Get("MR_Num" + lep + "MTinvMET/ewk")
h_qcd  = f.Get("MR_Num" + lep + "MTinvMET/qcd")

#h_ewk.Scale( 1. /(h_ewk.Integral() ) ) #h_data.Integral()
#h_qcd.Scale( 1. /( h_qcd.Integral() )  ) #h_data.Integral()
#h_data.Scale( 1. / h_data.Integral() )



doPlot(c, h_data, h_ewk, h_qcd, "step0")


## step1
first = doubleFit(h_data, h_ewk, h_qcd)

h_ewk.Scale(first[0])
h_qcd.Scale(first[1])
print "step 1 ewk scale: " + str(first[0])
print "step 1 qcd scale: " + str(first[1])
doPlot(c, h_data, h_ewk, h_qcd, "step1")

## step 2
h_dataqcdsub = h_data.Clone()
h_dataqcdsub.Add(h_qcd, -1)


#scale = h_data.Integral(h_data.GetBin(50), h_data.GetBin(120)) / h_ewk.Integral(h_ewk.GetBin(50), h_ewk.GetBin(120))

scale = singleFit(h_dataqcdsub, h_ewk, 50, 120)

print "step 2 scale: " + str(scale)
h_ewk.Scale(scale)
doPlot(c, h_data, h_ewk, h_qcd, "step2")



