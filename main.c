#!/usr/local/bin/python2

import re
import urllib
import urllib2
hurl='http://175game.com/'
		
class queue(object):
	def __init__(self):
		self.head=-1
		self.tail=-1
		self.url={}
		self.allurl={}

	def dequeue(self):
		self.head=self.head+1
		var=self.url.get(self.head)
		return var

	def enqueue(self,var):
		if self.allurl.get(var) == None:
			self.allurl[var] = 1
			self.tail=self.tail+1
			self.url[self.tail]=var

def GetPage(url):
	try:
		page = urllib2.urlopen(url)
	except	urllib2.URLError,e:
		return 
	content = page.read()
	return content

def main(targeturl):
	qurl=queue()
	qurl.enqueue(targeturl)

	regsrc=r'<img src=["]/(.*?.[jpg,png])["]'
	regsrcname=r'.*/(.*.[jpg,png])'
	reglink=r'<a href="/(.*?)".*>'

	comregsrc=re.compile(regsrc)
	comregsrcname=re.compile(regsrcname)
	comreglink=re.compile(reglink)
	
	url=qurl.dequeue()
	print url
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
			qurl.enqueue(hurl+onelink)	
		url=qurl.dequeue()
main(hurl)	
