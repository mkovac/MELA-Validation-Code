class Constant(object):
	"""A class that stores c constants"""
	def ___init___(self, gg_VA_2e2mu, gg_PidVA_2e2mu, gg_Ana_2e2mu, gg_PidAna_2e2mu, gg_VA_4eAnd4mu, gg_PidVA_4eAnd4mu, gg_Ana_4eAnd4mu, gg_PidAna_4eAnd4mu, qqb_VA_2e2mu, qqb_PidVA_2e2mu, qqb_Ana_2e2mu, qqb_PidAna_2e2mu, qqb_VA_4eAnd4mu, qqb_PidVA_4eAnd4mu, qqb_Ana_4eAnd4mu, qqb_PidAna_4eAnd4mu):

		self.gg_VA_2e2mu        = gg_VA_2e2mu
		self.gg_PidVA_2e2mu     = gg_PidVA_2e2mu
		self.gg_Ana_2e2mu       = gg_Ana_2e2mu
		self.gg_PidAna_2e2mu    = gg_PidAna_2e2mu
		self.gg_VA_4eAnd4mu     = gg_VA_4eAnd4mu
		self.gg_PidVA_4eAnd4mu  = gg_PidVA_4eAnd4mu
		self.gg_Ana_4eAnd4mu    = gg_Ana_4eAnd4mu
		self.gg_PidAna_4eAnd4mu = gg_PidAna_4eAnd4mu

		self.qqb_VA_2e2mu        = qqb_VA_2e2mu
		self.qqb_PidVA_2e2mu     = qqb_PidVA_2e2mu
		self.qqb_Ana_2e2mu       = qqb_Ana_2e2mu
		self.qqb_PidAna_2e2mu    = qqb_PidAna_2e2mu
		self.qqb_VA_4eAnd4mu     = qqb_VA_4eAnd4mu
		self.qqb_PidVA_4eAnd4mu  = qqb_PidVA_4eAnd4mu
		self.qqb_Ana_4eAnd4mu    = qqb_Ana_4eAnd4mu
		self.qqb_PidAna_4eAnd4mu = qqb_PidAna_4eAnd4mu

f = open('constants.txt', 'r')

list = []
models = [ "H2_g1g5", "H2_g5", "H2_g4", "H2_g2", "H2_g3", "H2_g6", "H2_g7", "H2_g8", "H2_g9", "H2_g10" ]

for line in f:
	if "Model" in line:
		temp = line.split()[1]
#		print
#		print temp
		temp = Constant()
		list.append(temp)

	if "2e2mu, gg_VA" in line:
#		print line.split()[5]
		temp.gg_VA_2e2mu = line.split()[5]

	if "2e2mu, gg_PidVA" in line:
#		print line.split()[5]
		temp.gg_PidVA_2e2mu = line.split()[5]

	if "2e2mu, gg_ANA" in line:
#		print line.split()[5]
		temp.gg_Ana_2e2mu = line.split()[5]

	if "2e2mu, gg_PidANA" in line:
#		print line.split()[5]
		temp.gg_PidAna_2e2mu = line.split()[5]

	if "4eAnd4mu, gg_VA" in line:
#		print line.split()[5]
		temp.gg_VA_4eAnd4mu = line.split()[5]

	if "4eAnd4mu, gg_PidVA" in line:
#		print line.split()[5]
		temp.gg_PidVA_4eAnd4mu = line.split()[5]

	if "4eAnd4mu, gg_ANA" in line:
#		print line.split()[5]
		temp.gg_Ana_4eAnd4mu = line.split()[5]

	if "4eAnd4mu, gg_PidANA" in line:
#		print line.split()[5]
		temp.gg_PidAna_4eAnd4mu = line.split()[5]

	if "2e2mu, qqb_VA" in line:
#		print line.split()[5]
		temp.qqb_VA_2e2mu = line.split()[5]

	if "2e2mu, qqb_PidVA" in line:
#		print line.split()[5]
		temp.qqb_PidVA_2e2mu = line.split()[5]

	if "2e2mu, qqb_ANA" in line:
#		print line.split()[5]
		temp.qqb_Ana_2e2mu = line.split()[5]

	if "2e2mu, qqb_PidANA" in line:
#		print line.split()[5]
		temp.qqb_PidAna_2e2mu = line.split()[5]

	if "4eAnd4mu, qqb_VA" in line:
#		print line.split()[5]
		temp.qqb_VA_4eAnd4mu = line.split()[5]

	if "4eAnd4mu, qqb_PidVA" in line:
#		print line.split()[5]
		temp.qqb_PidVA_4eAnd4mu = line.split()[5]

	if "4eAnd4mu, qqb_ANA" in line:
#		print line.split()[5]
		temp.qqb_Ana_4eAnd4mu = line.split()[5]

	if "4eAnd4mu, qqb_PidANA" in line:
#		print line.split()[5]
		temp.qqb_PidAna_4eAnd4mu = line.split()[5]


# GG
print "gg_VA 2e2mu"
print "==============================="
for i in range(0,10):
	print "if ( myModel_ == TVar::" + models[i] + " ) constant = " + list[i].gg_VA_2e2mu + ";"

print

print "gg_PidVA 2e2mu"
print "==============================="
for i in range(0,10):
	print "if ( myModel_ == TVar::" + models[i] + " ) constant = " + list[i].gg_PidVA_2e2mu + ";"

print

print "gg_ANA 2e2mu"
print "==============================="
for i in range(0,10):
	print "if ( myModel_ == TVar::" + models[i] + " ) constant = " + list[i].gg_Ana_2e2mu + ";"

print

print "gg_PidANA 2e2mu"
print "==============================="
for i in range(0,10):
	print "if ( myModel_ == TVar::" + models[i] + " ) constant = " + list[i].gg_PidAna_2e2mu + ";"

print

print "gg_VA 4eAnd4mu"
print "==============================="
for i in range(0,10):
	print "if ( myModel_ == TVar::" + models[i] + " ) constant = " + list[i].gg_VA_4eAnd4mu + ";"

print

print "gg_PidVA 4eAnd4mu"
print "==============================="
for i in range(0,10):
	print "if ( myModel_ == TVar::" + models[i] + " ) constant = " + list[i].gg_PidVA_4eAnd4mu + ";"

print

print "gg_ANA 4eAnd4mu"
print "==============================="
for i in range(0,10):
	print "if ( myModel_ == TVar::" + models[i] + " ) constant = " + list[i].gg_Ana_4eAnd4mu + ";"

print

print "gg_PidANA 4eAnd4mu"
print "==============================="
for i in range(0,10):
	print "if ( myModel_ == TVar::" + models[i] + " ) constant = " + list[i].gg_PidAna_4eAnd4mu + ";"

print

# QQB
print "qqb_VA 2e2mu"
print "==============================="
for i in range(10,20):
	print "if ( myModel_ == TVar::" + models[i-10] + " ) constant = " + list[i].qqb_VA_2e2mu + ";"

print

print "qqb_PidVA 2e2mu"
print "==============================="
for i in range(10,20):
	print "if ( myModel_ == TVar::" + models[i-10] + " ) constant = " + list[i].qqb_PidVA_2e2mu + ";"

print

print "qqb_ANA 2e2mu"
print "==============================="
for i in range(10,20):
	print "if ( myModel_ == TVar::" + models[i-10] + " ) constant = " + list[i].qqb_Ana_2e2mu + ";"

print

print "qqb_PidANA 2e2mu"
print "==============================="
for i in range(10,20):
	print "if ( myModel_ == TVar::" + models[i-10] + " ) constant = " + list[i].qqb_PidAna_2e2mu + ";"

print

print "qqb_VA 4eAnd4mu"
print "==============================="
for i in range(10,20):
	print "if ( myModel_ == TVar::" + models[i-10] + " ) constant = " + list[i].qqb_VA_4eAnd4mu + ";"

print

print "qqb_PidVA 4eAnd4mu"
print "==============================="
for i in range(10,20):
	print "if ( myModel_ == TVar::" + models[i-10] + " ) constant = " + list[i].qqb_PidVA_4eAnd4mu + ";"

print

print "qqb_ANA 4eAnd4mu"
print "==============================="
for i in range(10,20):
	print "if ( myModel_ == TVar::" + models[i-10] + " ) constant = " + list[i].qqb_Ana_4eAnd4mu + ";"

print

print "qqb_PidANA 4eAnd4mu"
print "==============================="
for i in range(10,20):
	print "if ( myModel_ == TVar::" + models[i-10] + " ) constant = " + list[i].qqb_PidAna_4eAnd4mu + ";"

print