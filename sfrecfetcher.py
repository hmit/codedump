from HTMLParser import HTMLParser

import cookielib
import pprint
import urllib2

class SFRecHTMLParser(HTMLParser):

    def do_init(self):
        dictt = {
            'start_table': False,
            'maybe_interesting_title': '',
            'title_data': '',
            'more_requests': {},
            }
        for k, v in dictt.iteritems():
            if not hasattr(self, k):
                setattr(self, k, v)

    def handle_starttag(self, tag, attrs):
        self.do_init()
        if tag == 'table':
            self.start_table = True
        if not self.maybe_interesting_title and not len(self.title_data.strip()):
            # keep on collecting the identical tags to title tags until end_tag pop matches the pushed tags (like parenthesis matching)
            self.maybe_interesting_title = 'div' if len(self.is_present(('class', 'activity-title'), attrs)) else ''

        if self.is_present(('title', 'Show Courses'), attrs):
            title_data = self.title_data.lower()
            self.maybe_interesting_title = ''
            self.title_data = ''
            if 'adult' in title_data:
                self.add_request(title_data, attrs)

    def handle_endtag(self, tag):
        if tag == 'table':
            self.start_table = False
        if len(tag) and tag == self.maybe_interesting_title:
            self.maybe_interesting_title = ''

    def handle_data(self, data):
        if self.maybe_interesting_title:
            self.collect_title_data(data.strip())

    def collect_title_data(self, data):
        self.title_data += data

    def is_present(self, tup, attrs):
        filtered = filter(lambda (k, val): tup[0].lower() in k.lower() and tup[1].lower() in val.lower(), attrs)
        return filtered

    def add_request(self, course, attrs):
        req = filter(lambda (k, _): 'onclick' in k.lower(), attrs)[0][1]
        self.more_requests[course] = req

    def get_more_requests(self):
        return self.more_requests

    def add_more_data(self, data):
        if len(data.strip()) <= 0:
            return
        if hasattr(self, 'data'):
            self.data.append(data)
        else:
            self.data = [data]


class MyCookiePolicy(cookielib.DefaultCookiePolicy):
    def set_ok(self, cookie, request):
        if not cookielib.DefaultCookiePolicy.set_ok(self, cookie, request):
            return False


jar = cookielib.FileCookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(jar))
response = opener.open("https://www.sfreconline.org/Activities/ActivitiesAdvSearch.asp")
response1 = opener.open("https://www.sfreconline.org/Activities/ActivitiesAdvSearch.asp?SectionId=12&BasicSearch=True&_=1444160881853&ajax=true")
base_url = "https://www.sfreconline.org/Activities/ActivitiesDetails.asp?" #AdvPage=true&ProcessWait=N&aid=659&ComplexId=0&sEcho=1&iColumns=8&sColumns=&iDisplayStart=0&iDisplayLength=10&ajax=true"
# opener.addheaders.append(('Cookie',
parser = SFRecHTMLParser()
html = response1.read()
parser.feed(html)

reqs = parser.get_more_requests()
pprint.pprint(reqs)
isdone = False
import code; code.interact(local=locals())
for (k, v) in reqs.iteritems():
    if isdone: break
    isdone = True
    suffix = v.split('(')[1].split(',')[0].split("?")[-1][:-1]
    url = base_url + suffix + "ajax=True"
    resp = opener.open(url)
    print resp.read()


    #https://www.sfreconline.org/Activities/ActivitiesDetails.asp?AdvPage=true&ProcessWait=N&aid=668&ComplexId=0&sEcho=1&iColumns=8&sColumns=&iDisplayStart=0&iDisplayLength=10&ajax=true
