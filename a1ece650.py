# importing in-built libraries
import re,sys

# variables for all error messages
ENTER_VALD_COMMAND = "Enter a valid command to add, change, remove or generate"
STREET_ALREADY_EXISTS = "street already exsists"
NO_STREET_EXISTS = "No street with such name exists"
VALID_INPUT_FOR_STREET_NAME = "Enter a valid input for street name"
VALID_INPUT = "Enter a valid input"
VALID_INPUT_FOR_COORDINATES = "Enter a valid input for coordinates"
VALID_INPUT_FOR_REMOVE = "Enter valid input for remove"
NO_STREET = "No streets exists"

# class for street having 
# 1. list of lines and 
# 2. street name    
class S:
    def __init__(self, lines, streetName=""):
        self.all_lines = lines
        self.name = streetName

# class for point having :
# 1. x coordinate 
# 2. y coordinate 
# 3. index 
# 4.istersection
class P:
    def __init__(self, xCord=0.0, yCord=0.0, index = 0, intersection = False):
        self.index = index
        self.intersection = intersection
        self.x = float(xCord)
        self.y = float(yCord)

# class for intersection having 3 points
class IS:
    def __init__(self, point1, point2, point3):
        self.A = P(point1.x, point1.y)
        self.B = P(point2.x, point2.y)
        self.C = P(point3.x, point3.y)

# class for Line having: 
# 1.Name of street 
# 2. point1 
# 3.point2
class L:
    def __init__(self, point1, point2, nameOfStreet=""):
        self.name = nameOfStreet
        self.pointA = P(point1.x, point1.y)
        self.pointB = P(point2.x, point2.y)
    

# method to check if the street with similar name already exists
def isStreetAlreadyExist(streetName):
    # get the length of length
    length = len(all_streets)
    # loop over all_street list
    for street in range(length):
        # if streetName is equal to any name in list 
        # irrespective of case then print error
        SNFL = all_streets[street].name.upper()
        SN = streetName.upper()
        if SNFL == SN:
            # print the error and return true
            print("Error:", STREET_ALREADY_EXISTS)
            return True
    return False

# method to add the coordinates of the street in the list
def appendInPointsFetched(coordinateList):
    # initializing the list
    pointsOfCurrentStreet = list()
    for coord in coordinateList:
        A = coord[0]
        B = coord[1]
        # appending the coordinates to the list
        pointsOfCurrentStreet.append(P(A, B))
    # return list
    return pointsOfCurrentStreet

# method to remove the street
def remove(NameofStreet):
    isStreetDeleted = False
    # get the length of length
    length = len(all_streets)
    # loop over the all_streets list
    for street in range(length):
        # if streetName is equal to any name in list 
        # irrespective of case then pop the street from the list
        # and set isStreetDeleted to true
        SNFL = all_streets[street].name.upper()
        SN = NameofStreet.upper()
        if SNFL ==  SN:
            # pop the element from list
            all_streets.pop(street)
            #print(all_streets)
            isStreetDeleted = True
            break
    # is isStreetDeleted is still false then no street exists
    if isStreetDeleted is False:
        # print the error
        print("Error:", NO_STREET_EXISTS)
    return isStreetDeleted

# method to add the street
def addStreet(street, arrayOfCoordinate):    
    # check if street with same name already exists
    alreadyExists = isStreetAlreadyExist(street)
    # if yes then return
    if alreadyExists is True:
        return
    else:
        # add the coordinate points in list
        all_points = appendInPointsFetched(arrayOfCoordinate)
        #print(all_points)
        l = len(all_points)
        # for every point in all_points make a line of point and it's next point 
        # and add it to all_lines list                                      
        for posi, pt in enumerate(all_points):
            if posi < (l - 1):
                A = all_points[posi]
                B = all_points[posi + 1]
                all_lines.append(L(A, B))
        #print(all_lines)
        all_streets.append(S(all_lines, street))
        #for i in range(len(all_streets)):
            #print(all_streets[i].all_lines)
        #print(all_streets)

# method to validate if input given is correct or not
def validInput(input):
    # regex to checl the input
    inputRegex = re.compile(r"^(a|c|r|g)\s+(\"[(a-zA-Z)|( )]+\")\s*((\([-]?[0-9]+\,[-]?[0-9]+\)\s*)*)$")
    # fetching the list of input based on regex
    ListofInput = inputRegex.findall(input)
    # returning the list
    return ListofInput

# method to get the street name from the input string
def getStreetName(input):
    # get list of inputs
    ListofInput  = validInput(input)
    # if list of input = 0 then throw error and return
    if len(ListofInput) == 0:
        # printing the error
        print("Error:", VALID_INPUT_FOR_STREET_NAME)
        return
    else:
        # fetch the street name with apostrophe's
        #replace the apostrophes with blank
        streetName = getStreetNameTest(ListofInput[0][1])
    # return the street name
    return streetName


def getStreetNameTest(input):
    # fetch the street name with apostrophe's
    streetNamewithapos = input
    #replace the apostrophes with blank
    streetName = streetNamewithapos.replace("\"","")
    return streetName

# method to validate if coordinates are passed in correct format or not
def validateInputForAddOrChange(input):
    # get list of inputs
    ListofInput  = validInput(input)
    # if list of input = 0 then throw error and return
    if len(ListofInput) == 0:
        # print error
        print("Error:", VALID_INPUT)
        return
    else:
        # fetch the coordinates from input
        coordinates = ListofInput[0][2]
        # making regex for it
        coordinateRegex = re.compile(r'\s*\([-]?[0-9]+,[-]?[0-9]+\)\s*')
        # fetching the data
        coordinatesList = coordinateRegex.findall(coordinates)
        # initializing the empty list
        listofCoordinates =list()
        # if fetched data is empty then print error
        if len(coordinatesList) == 0:
            print("Error:",VALID_INPUT_FOR_COORDINATES)
            return
        # loop through every coordinate to get the exact format of it
        for x in coordinatesList:
            x = x.replace("'", "")
            x = x.strip()
            listofCoordinates.append(eval(x))
    # return list of coordinates
    return listofCoordinates

# method to get the input and operate further based on the type of command
def getInput(input):
    # regex to check command
    commandRegEx = re.compile(r"^(a|c|r|g)\s*")
    # fetching the command
    command = commandRegEx.findall(input)
    # if command is null then throw error
    if (len(command) == 0):
        # printing the error
        print("Error:", ENTER_VALD_COMMAND)
        return
    # if command == a
    if (command[0] == "a"):
        # get the street name
        streetName = getStreetName(input)
        if (streetName != None):
            # get list of coordinates
            ListofCoordinates = validateInputForAddOrChange(input)
            if (ListofCoordinates != None):
                #print(ListofCoordinates)
                # cal a method to add the street
                addStreet(streetName,ListofCoordinates)
    # if command is c
    elif (command[0] == "c"):
        # get street name
        streetName = getStreetName(input)
        if (streetName != None):
            # fetch list of coordinates
            ListofCoordinates = validateInputForAddOrChange(input)
            if (ListofCoordinates != None):
                #print(ListofCoordinates)
                # cal remove method to remove the street first
                validForRemove = remove(streetName)
                if(validForRemove):
                    # then call add street method to add it
                    addStreet(streetName,ListofCoordinates)
    # if command is r
    elif (command[0] == "r"):
        # regex
        regexForRemove = re.compile(r"^(a|c|r|g)\s+((\"[(a-zA-Z)|( )]+\")\s*)$")
        # fetching the list based on regex
        inputForRemove = regexForRemove.findall(input)
        # if len = 0 then throw error
        if len(inputForRemove) == 0:
            # printing the error
            print("Error:", VALID_INPUT_FOR_REMOVE)
        else:
            # fetch the street name
            streetName = getStreetNameTest(inputForRemove[0][1])
            streetName = streetName.strip()
            # call remove method to remove the street 
            remove(streetName)
    # if command ==g 
    elif (command[0] == "g"):
        # if no street is present then print error
        if(len(all_streets) == 0):
            print("Error:", NO_STREET)
            return
        # else call method to generate graph
        generateGraph()

# method to get and print vertices and edges
def generateGraph():
    # varibale intialization
    global indeces
    indeces = 0
    vertices = list()
    intersection_points = list()
    IntS = list()
    x = 0
    # get the length of the list
    length = len(all_streets)
    # looping through the all streets
    while x < length:
        # looping the sreet with every other street
        for y in range(x+1, length):
            # for every line in street loop it with every other line in other street
            for line_street1 in all_streets[x].all_lines:
                for line_street2 in all_streets[y].all_lines:
                    # call a method to find the intersection point
                    x_intersect, y_intersect = doLineIntersect(line_street1,line_street2)
                    #print(x_intersect,y_intersect)
                    if x_intersect == False and y_intersect==False:
                        continue
                    else:
                        intersection_points.append(P(x_intersect,y_intersect))
                        # call a method to add the point in vertex list
                        templist = [(x_intersect,y_intersect), (line_street1.pointA.x, line_street1.pointA.y), (line_street1.pointB.x,line_street1.pointB.y), (line_street2.pointA.x, line_street2.pointA.y), (line_street2.pointB.x, line_street2.pointB.y)]
                        for i in range(0, len(templist)):
                            addVertex(vertices, templist[i][0], templist[i][1], True)
                        #addVertex(vertices, x_intersect, y_intersect,True)
                        #addVertex(vertices, line_street1.pointA.x, line_street1.pointA.y, False)
                        #print(vertices[1].x, vertices[1].y)
                        #addVertex(vertices, line_street1.pointB.x, line_street1.pointB.y, False)
                        #print(vertices[2].x, vertices[2].y)
                        #addVertex(vertices, line_street2.pointA.x, line_street2.pointA.y, False)
                        #print(vertices[3].x, vertices[3].y)
                        #addVertex(vertices, line_street2.pointB.x, line_street2.pointB.y, False)
                        #print(vertices[4].x, vertices[4].y)
                        IntS.append(IS(P(line_street1.pointA.x, line_street1.pointA.y), P(x_intersect, y_intersect), P(line_street1.pointB.x, line_street1.pointB.y)))
                        IntS.append(IS(P(line_street2.pointA.x, line_street2.pointA.y), P(x_intersect, y_intersect), P(line_street2.pointB.x, line_street2.pointB.y)))
        x +=1
    # call a mthod to print vertices
    printVertices(vertices)
    # call a method to print edges
    getAndPrintEdge(vertices, IntS, intersection_points)

# method to check if 2 lines intersect or not
def doLineIntersect(l1, l2):
    # getting x and y corrdinates of line 1
    x1,x2,y1,y2 = l1.pointA.x, l1.pointB.x, l1.pointA.y, l1.pointB.y
    # getting x and y corrdinates of line 2
    x3,x4,y3,y4 = l2.pointA.x, l2.pointB.x, l2.pointA.y, l2.pointB.y
    try:
        # making calculations to get numerator
        d = (((x2 - x1) * (y4 - y3)) - ((y2 - y1) * (x4 - x3)))
        ua = ((x4 - x3) * (y1 - y3)) - ((y4 - y3) * (x1 - x3))
        # note:  if d =0 then it will go to except block
        numerator_x = ua/d
        ub = ((x2 - x1) * (y1 - y3)) - ((y2 - y1) * (x1 - x3))
        numerator_y = ub/d
        # getting intersection points
        if ((numerator_x>=0 and numerator_x<=1) and (numerator_y>=0 and numerator_y<=1)):
            x_intersect = x1 + numerator_x * (x2 - x1)
            y_intersect = y1 + numerator_x * (y2 - y1)
            # finding if intersection point lies in range or not
            # if yes then return the point
            if x_intersect>=min(x1,x2) and x_intersect<=max(x1,x2) and y_intersect>=min(y1,y2) and y_intersect<=max(y1,y2):
                return x_intersect, y_intersect
            # else return false
            else:
                return False, False
        else:
            return False, False
    # in case of exception
    except Exception:
        return False, False

# method to print the vertices in the format
def printVertices(vertices):
    # get the length of vertices
    length = len(vertices)
    print("V "+ str(length))
    # print("V = {")
    # # loop through every element in vertex list
    # for i in range(length):
    #     a = vertices[i].index
    #     b = vertices[i].x
    #     c = vertices[i].y
        
    #     if (a%1==0):
    #         a = int(a)
    #         a1 = str(a)
    #     else:
    #         a1 = f"{a:.2f}"
        
    #     if (b%1==0):
    #         b = int(b)
    #         b1 = str(b)
    #     else:
    #         b1 = f"{b:.2f}"

    #     if (c%1==0):
    #         c = int(c)
    #         c1 = str(c)
    #     else:
    #         c1 = f"{c:.2f}"    
        
    #     # printing according to the desired format
    #     print(" "+a1 + " : ("+ b1 + ","+ c1 + ")")
    # print("}")

# method to append the edges in the list
def appendInEdgeList(v, edges, point0, point1, point2, new):
    # if v is empty
    if v == []:
        appendInVertexList(v, point0,point1,point2)
        #append the edges along with intersection in edges list
        edges.append((point0, point1))
        edges.append((point1, point2))
    # is v is not empty
    else:
        appendInVertexList(v, point0,point2,point1)
        # set will remove the repeating onces and list will convert the set back to list
        v = list(set(v))
        new = sorted(v, key=lambda x: (float(x[0])))
    # loop through the list and add the 2 lines to the edge
    for right in range(0, len(new) - 1):
        l1 = new[right]
        l2 = new[right + 1]
        edges.append((l1, l2))

#method to append the points in vertex list
def appendInVertexList(v, point0, point1, point2): 
        # appending p0 in v
        v.append(point0) 
        # appending p1 in v                 
        v.append(point1)
        # appending p2 in v
        v.append(point2)

# Method to find the edge and print it in certain format
def getAndPrintEdge(vertices, i_set, i_p):
    edges = []
    # loop through the intersection set
    for i in i_set:
        # as intersection set contains 3 points
        # fetching p0, p1, p2
        p0 = (i.A.x, i.A.y)
        p1 = (i.B.x, i.B.y)
        p2 = (i.C.x, i.C.y)
        v = []
        new = []
        # loop through intersection point again each intersection set
        for j in i_p:  
            #if these are collinear the append in the vertex
            if collinear((j.x, j.y), p0, p2):
                if (j.x, j.y) != p1:
                    v.append((j.x, j.y))

        appendInEdgeList(v, edges, p0, p1, p2, new)

        #for r in range(0, len(v) - 1):
        #    edges.append((v[r], v[r + 1]))
    # method to print the edges
    #printEdge(list(set(edges)), vertices)
    l = list(set(edges))
    # print("E = {")
    a = 0
    edgep = ""
    # loop over the list of edges
    while a < len(l):
        i1, i2 = 0, 0
        b=0
        # for every edge list over the vertex to find the index corresponding to the point
        while b < len(vertices):
            # if it matches the point it in i1 and i2
            tempx1 = l[a][0][0]
            tempy1 = l[a][0][1]
            tempx2 = l[a][1][0]
            tempy2 = l[a][1][1]
            if tempx1 == vertices[b].x and tempy1 == vertices[b].y:
                i1 = vertices[b].index
            if tempx2 == vertices[b].x and tempy2 == vertices[b].y:
                i2 = vertices[b].index
            b+=1
        # if i1 != i2
        if i1 != i2:
            # the below block prints the edges in certain format with ',' at the end
            # but for the last edge the comma is handled
            edgep = edgep+ "<" + str(i1) + "," + str(i2) + ">"
            if a == len(l) - 1:
                edgep = edgep
            else:
                edgep = edgep + ","
        #edges.append(L(P(l[a][0][0], l[a][0][1], int(i1), True),
        #                  P(l[a][1][0], l[a][1][1], int(i2), True)))
        a+=1
    print("E {" + edgep + "}")


# method to check if 3 points are collinear or not
def collinear(A,B,C):
    #d1 = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))
    #d2 = sqrt((x3-x2)*(x3-x2) + (y3-y2)*(y3-y2))
    #d3 = sqrt((x3-x1)*(x3-x1) + (y3-y1)*(y3-y1))
    #if ((d1+d2)==d3):
    #    return True
    #else:
    #    return False
    a1 = B[0] - A[0] 
    a2 = C[0] - A[0] 
    b1 = B[1] - A[1] 
    b2 = C[1] - A[1] 
    temp1 = 1e-12
    temp2 = abs(a1 * b2 - a2 *b1)
    # if 1e-12 is greater than temp2 then return true
    if temp1 > temp2:
        return True
    # else return false
    else:
        return False

# method to add the vertex
def addVertex(vertices, x, y, isIntersection):
    global indeces
    g = 1
    i=0
    # get the length of vertices
    length = len(vertices)
    # loop over every vertex
    while i < length:
        g = 1
        # if vertex is already there then set g=0 and don't add it in vertex list
        if vertices[i].y == y and vertices[i].x == x:
            g = 0
            break
        i +=1
    # add in vertex list
    if g == 1:
        vertices.append(P(x, y, indeces, isIntersection))
        indeces +=1

# main method
def main():
    # global variables
    global all_points
    global all_lines
    global all_streets
    global edges
    # initializing empty lists
    edges = list()
    all_points  = list()
    all_lines = list ()
    all_streets = list()
    # till the time there is no keyboard interruption, 
    # keep taking the inputs
    # except exit the program
    try:
        while True:
            # print ("I am from a1 python ")
            input1 = input()
            # for x in sys.stdin:
            #     print(x)
            # input1 = sys.stdin.readline()
            
            # if EOF reaches 
            # then break the while loop and exit the program
            if (len(input1)==0):
                break
            # if (not input1):
            #     print("exicting python a1 ")
            #     break
            
            # method to get the input and 
            # call the further methods based on the command given. 
            # Also, give the error's accordingly
            getInput(input1)
            all_points, all_lines  =list(), list()
    except KeyboardInterrupt:
        sys.exit(0)
    except EOFError as e:
        sys.exit(0)
    except BrokenPipeError as e:
        sys.exit(0)


# call the main function
if __name__=="__main__":
    main()
