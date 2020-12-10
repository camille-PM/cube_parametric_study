# -*- coding: mbcs -*-
from abaqus import *
from abaqusConstants import *
session.Viewport(name='Viewport: 1', origin=(0.0, 0.0), width=317.217193603516, 
    height=191.581481933594)
session.viewports['Viewport: 1'].makeCurrent()
from caeModules import *
from driverUtils import executeOnCaeStartup
executeOnCaeStartup()
openMdb('base_model.cae')
session.viewports['Viewport: 1'].setValues(displayedObject=None)
session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
    referenceRepresentation=ON)
p = mdb.models['Model-1'].parts['Scaffold']
f, e = p.faces, p.edges
t = p.MakeSketchTransform(sketchPlane=f[0], sketchUpEdge=e[3], 
    sketchPlaneSide=SIDE1, sketchOrientation=RIGHT, origin=(1.5, 0.0, 1.5))
s = mdb.models['Model-1'].ConstrainedSketch(name='__profile__', sheetSize=9.0, 
    gridSpacing=0.22, transform=t)
g, v, d, c = s.geometry, s.vertices, s.dimensions, s.constraints
s.setPrimaryObject(option=SUPERIMPOSE)
p = mdb.models['Model-1'].parts['Scaffold']
p.projectReferencesOntoSketch(sketch=s, filter=COPLANAR_EDGES)
s.rectangle(point1=(-MAGIC00, MAGIC00), point2=(-MAGIC01, MAGIC01))
s.rectangle(point1=(-MAGIC02, MAGIC03), point2=(-MAGIC04, -MAGIC03))
s.rectangle(point1=(-MAGIC05, -MAGIC06), point2=(-MAGIC06, -MAGIC05))
s.linearPattern(geomList=(g[6], g[7], g[8], g[9], g[10], g[11], g[12], g[13], 
    g[14], g[15], g[16], g[17]), vertexList=(), number1=3, spacing1=1.0, 
    angle1=0.0, number2=1, spacing2=0.9, angle2=90.0)
p = mdb.models['Model-1'].parts['Scaffold']
f1, e1 = p.faces, p.edges
p.CutExtrude(sketchPlane=f1[0], sketchUpEdge=e1[3], sketchPlaneSide=SIDE1, 
    sketchOrientation=RIGHT, sketch=s, flipExtrudeDirection=OFF)
s.unsetPrimaryObject()
del mdb.models['Model-1'].sketches['__profile__']
p = mdb.models['Model-1'].parts['Scaffold']
f, e = p.faces, p.edges
t = p.MakeSketchTransform(sketchPlane=f[39], sketchUpEdge=e[113], 
    sketchPlaneSide=SIDE1, sketchOrientation=RIGHT, origin=(0.0, 1.5, 1.5))
s1 = mdb.models['Model-1'].ConstrainedSketch(name='__profile__', 
    sheetSize=10.39, gridSpacing=0.25, transform=t)
g, v, d, c = s1.geometry, s1.vertices, s1.dimensions, s1.constraints
s1.setPrimaryObject(option=SUPERIMPOSE)
p = mdb.models['Model-1'].parts['Scaffold']
p.projectReferencesOntoSketch(sketch=s1, filter=COPLANAR_EDGES)
s1.rectangle(point1=(-MAGIC07, MAGIC07), point2=(-MAGIC08, MAGIC08))
s1.rectangle(point1=(-MAGIC09, MAGIC10), point2=(-MAGIC11, -MAGIC10))
s1.rectangle(point1=(-MAGIC12, -MAGIC13), point2=(-MAGIC13, -MAGIC12))
s1.linearPattern(geomList=(g[6], g[7], g[8], g[9], g[10], g[11], g[12], g[13], 
    g[14], g[15], g[16], g[17]), vertexList=(), number1=3, spacing1=1.0, 
    angle1=0.0, number2=1, spacing2=1.039, angle2=90.0)
p = mdb.models['Model-1'].parts['Scaffold']
f1, e1 = p.faces, p.edges
p.CutExtrude(sketchPlane=f1[39], sketchUpEdge=e1[113], sketchPlaneSide=SIDE1, 
    sketchOrientation=RIGHT, sketch=s1, flipExtrudeDirection=OFF)
s1.unsetPrimaryObject()
del mdb.models['Model-1'].sketches['__profile__']
p = mdb.models['Model-1'].parts['Scaffold']
f, e = p.faces, p.edges
t = p.MakeSketchTransform(sketchPlane=f[154], sketchUpEdge=e[548], 
    sketchPlaneSide=SIDE1, sketchOrientation=RIGHT, origin=(0.0, 0.0, 3.0))
s = mdb.models['Model-1'].ConstrainedSketch(name='__profile__', 
    sheetSize=10.39, gridSpacing=0.25, transform=t)
g, v, d, c = s.geometry, s.vertices, s.dimensions, s.constraints
s.setPrimaryObject(option=SUPERIMPOSE)
p = mdb.models['Model-1'].parts['Scaffold']
p.projectReferencesOntoSketch(sketch=s, filter=COPLANAR_EDGES)
s.rectangle(point1=(-MAGIC14, MAGIC14), point2=(-MAGIC15, MAGIC15))
s.linearPattern(geomList=(g[6], g[7], g[8], g[9]), vertexList=(), number1=3, 
    spacing1=1.0, angle1=0.0, number2=3, spacing2=1.0, angle2=270.0)
p = mdb.models['Model-1'].parts['Scaffold']
f1, e1 = p.faces, p.edges
p.CutExtrude(sketchPlane=f1[154], sketchUpEdge=e1[548], sketchPlaneSide=SIDE1, 
    sketchOrientation=RIGHT, sketch=s, flipExtrudeDirection=OFF)
s.unsetPrimaryObject()
del mdb.models['Model-1'].sketches['__profile__']
a = mdb.models['Model-1'].rootAssembly
a.regenerate()
session.viewports['Viewport: 1'].setValues(displayedObject=a)
session.viewports['Viewport: 1'].assemblyDisplay.setValues(
    optimizationTasks=OFF, geometricRestrictions=OFF, stopConditions=OFF)
a.InstanceFromBooleanCut(name='Callus', 
    instanceToBeCut=mdb.models['Model-1'].rootAssembly.instances['Full_tissue-1'], 
    cuttingInstances=(a.instances['Scaffold-1'], ), originalInstances=SUPPRESS)
a.features['Scaffold-1'].resume()
p = mdb.models['Model-1'].parts['Scaffold']
s = p.faces
side1Faces = s.getSequenceFromMask(mask=(
    '[#ffffffff:8 #ffffff3f #ffffffff #9fffffff #fff ]', ), )
p.Surface(side1Faces=side1Faces, name='internal_surfaces')
p = mdb.models['Model-1'].parts['Callus']
s = p.faces
side1Faces = s.getSequenceFromMask(mask=('[#ffffffff:12 #3fffffff ]', ), )
p.Surface(side1Faces=side1Faces, name='external_surf')
a1 = mdb.models['Model-1'].rootAssembly
a1.regenerate()
p = mdb.models['Model-1'].parts['Callus']
session.viewports['Viewport: 1'].setValues(displayedObject=p)
session.viewports['Viewport: 1'].partDisplay.setValues(mesh=ON)
session.viewports['Viewport: 1'].partDisplay.meshOptions.setValues(
    meshTechnique=ON)
session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
    referenceRepresentation=OFF)
c = p.cells
pickedRegions = c.getSequenceFromMask(mask=('[#1 ]', ), )
p.setMeshControls(regions=pickedRegions, elemShape=TET, technique=FREE)
elemType1 = mesh.ElemType(elemCode=C3D20R)
elemType2 = mesh.ElemType(elemCode=C3D15)
elemType3 = mesh.ElemType(elemCode=C3D10)
cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
pickedRegions =(cells, )
p.setElementType(regions=pickedRegions, elemTypes=(elemType1, elemType2, 
    elemType3))
p.seedPart(size=0.2, deviationFactor=0.1, minSizeFactor=0.1)
p.generateMesh()
p = mdb.models['Model-1'].parts['Scaffold']
session.viewports['Viewport: 1'].setValues(displayedObject=p)
p.generateMesh()
a1 = mdb.models['Model-1'].rootAssembly
a1.regenerate()
mdb.jobs['Job-1'].writeInput(consistencyChecking=OFF)