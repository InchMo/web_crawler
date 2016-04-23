#!/usr/local/bin/python2

import re
import urllib
import urllib2
hurl='http://175game.com/'
		
class strack(object):
	def init(self):
		self.point=-1
		self.url={}
		self.allurl={}
	def pop(self):
		if self.point >= 0:
			var = self.url[self.point]
		        self.point = self.point - 1
			return var 
		return None
	def push(self,var):
		if self.allurl.get(var) == None:
			self.point = self.point + 1
			self.url[self.point] = var		
			self.allurl[var] = 1

def GetPage(url):
	try:
		page = urllib2.urlopen(url)
	except	urllib2.URLError,e:
		return 
	content = page.read()
	return content

def main(targeturl):
	surl=strack()
	surl.init()
	surl.push(targeturl)

	regsrc=r'<img src=["]/(.*?.[jpg,png])["]'
	regsrcname=r'.*/(.*.[jpg,png])'
	reglink=r'<a href="/(.*?)".*>'

	comregsrc=re.compile(regsrc)
	comregsrcname=re.compile(regsrcname)
	comreglink=re.compile(reglink)
	
	url=surl.pop()
	ResourceUrlList = []
	LinkList = []
	while url!=None:
		content=GetPage(url)
		if content != None:
			ResourceUrlList=re.findall(comregsrc,content)
			LinkList=re.findall(comreglink,content)
		for oneurl in ResourceUrlList:
			filename=re.findall(comregsrcname,oneurl)
			oneurl=hurl+oneurl
			print oneurl
			u=urllib.urlopen(oneurl)
			data=u.read()
			f=open(filename[0],'wb')
			f.write(data)
			f.close()
		for onelink in LinkList:
			surl.push(hurl+onelink)	
		url=surl.pop()
main(hurl)	
