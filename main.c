#!/usr/local/bin/python2

import re
import urllib

def GetPage(url):
	page = urllib.urlopen(url)
	content = page.read()
	return content

def GetResource(hurl,content):
	reg=r'src="(.*.[jpg,png])"'
	comreg=re.compile(reg)
	ResourceUrlList=re.findall(comreg,content)
	print ResourceUrlList
	count=0
	for oneurl in ResourceUrlList:
		oneurl=hurl+oneurl
		urllib.urlretrieve(oneurl,'%d.img' % count)
		count+=1	

url='http://175game.com'
GetResource(url,GetPage(url))	
