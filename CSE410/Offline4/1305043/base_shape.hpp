#include<math.h>
#include "bitmap_image.hpp"
#define pi (2*acos(0.0))

#define AMBIENT 0
#define DIFFUSE 1
#define SPECULR 2
#define REFLECT 3

#define EPS 0.00001
typedef struct pp
{
    double x,y,z;
}point;

typedef struct vv
{
    double x,y,z;
}vect;
double dotProduct(vect a, vect b)
{
    return a.x*b.x+a.y*b.y+a.z*b.z;
}
point movePointAlongvect(point pos,vect r, double scale)
{
    point tmp={pos.x+scale*r.x,pos.y+scale*r.y,pos.z+scale*r.z};
    return tmp;
}
vect crossProduct(vect a,vect b)
{
    vect tmp = {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
    return tmp;
}
vect scaleVector(vect a, double scale)
{
    vect tmp = {a.x*scale,a.y*scale,a.z*scale};
    return tmp;
}
vect vectSum(vect a, vect b)
{
    vect tmp={a.x+b.x,a.y+b.y,a.z+b.z};
    return tmp;
}
vect rotateVector(vect a,vect ref, double angle)
{
    vect tangent = crossProduct(ref,a);
    vect tmp = vectSum(scaleVector(tangent,sin(pi*angle/180.0)),scaleVector(a,cos(pi*angle/180.0)));
    return tmp;
}
vect normalizeVector(vect a) {
    double dd = a.x*a.x + a.y*a.y + a.z*a.z;
    dd = sqrt(dd);
    vect tmp = {a.x/dd,a.y/dd,a.z/dd};
    return tmp;
}
vect pointToVector(point tmp)
{
    return {tmp.x,tmp.y,tmp.z};
}
point vectorToPoint(vect tmp)
{
    return {tmp.x,tmp.y,tmp.z};
}
double vectorLength(vect tmp)
{
    return sqrt(tmp.x*tmp.x+tmp.y*tmp.y+tmp.z*tmp.z);
}

bool GT(double a, double b, double epsilon=EPS)
{
    return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

bool LT(double a, double b, double epsilon=EPS)
{
    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
bool EQ(double a, double b, double epsilon=EPS)
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
bool GTE(double a, double b)
{
    return GT(a,b)||EQ(a,b);
}
bool LTE(double a, double b)
{
    return LT(a,b)||EQ(a,b);
}
class LightRay{
public:
    point start;
    vect dir;
    LightRay(point stp,vect dir)
    {
        this->start = stp;
        this->dir = normalizeVector(dir);
    }
};
class BaseObject{
public:
    vect reference_point;
    double height,width,length,source_factor = 1.0;
    int shine;
    double color[3];
    double coeffs[4];
    bool colorSet;
    virtual void draw() = 0; //pure virtual function
    virtual double getIntersectingT(LightRay* r) = 0;
    virtual double  intersect(LightRay *r, double colorAt[3], int level){
        return -1;
    }
    virtual vect getNormal(point intersectionPoint) = 0;
    vect getReflection(vect normal, vect dirVector)
    {
        double scl = -2.0* dotProduct(normal,dirVector);
        vect tmp = scaleVector(normal,scl);
        tmp = vectSum(dirVector,tmp);
        return normalizeVector(tmp);
    }
    void setColor(double r, double g, double b){
        this->color[0] = r;
        this->color[1] = g;
        this->color[2] = b;
        colorSet = true;
    }
    void setShine(int shine)
    {
        this->shine = shine;
    }
    void setCoeffs(double a, double d,double s,double r)
    {
        this->coeffs[AMBIENT] = a;
        this->coeffs[DIFFUSE] = d;
        this->coeffs[SPECULR] = s;
        this->coeffs[REFLECT] = r;
    }
    void setSourceFactor(double val)
    {
        this->source_factor = val;
    }
};
extern int recursion_level;
extern vector<vect>lights;
extern vector<BaseObject*>objects;


class Sphere: public BaseObject
{
public:
    double eta = 3	;
    Sphere(point center,double radius)
    {
        this->reference_point = pointToVector(center);
        this->length = radius;
    }
    void draw()
    {
        //glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(color[0],color[1],color[2]);

        //printf("%lf %lf %lf\n",color[0],color[1],color[2] );
        point points[100][100];
        int i,j;
        double h,r;

        int stacks = 43;
        double radius = this->length;
        int slices = 43;

        //generate points
        for(i=0;i<=stacks;i++){
            h=radius*sin(((double)i/(double)stacks)*(pi/2));
            r=radius*cos(((double)i/(double)stacks)*(pi/2));
            for(j=0;j<=slices;j++)
            {
                points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
                points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
                points[i][j].z=h;
            }
        }
        //draw quads using generated points
        for(i=0;i<stacks;i++){
            //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            for(j=0;j<slices;j++){
                glBegin(GL_QUADS);{
                    //upper hemisphere
                    glVertex3f(points[i][j].x+(this->reference_point.x),points[i][j].y+(this->reference_point.y),points[i][j].z+(this->reference_point.z));
                    glVertex3f(points[i][j+1].x+(this->reference_point.x),points[i][j+1].y+(this->reference_point.y),points[i][j+1].z+(this->reference_point.z));
                    glVertex3f(points[i+1][j+1].x+(this->reference_point.x),points[i+1][j+1].y+(this->reference_point.y),points[i+1][j+1].z+(this->reference_point.z));
                    glVertex3f(points[i+1][j].x+(this->reference_point.x),points[i+1][j].y+(this->reference_point.y),points[i+1][j].z+(this->reference_point.z));
                    //lower hemisphere
                    glVertex3f(points[i][j].x+(this->reference_point.x),points[i][j].y+(this->reference_point.y),-points[i][j].z+(this->reference_point.z));
                    glVertex3f(points[i][j+1].x+(this->reference_point.x),points[i][j+1].y+(this->reference_point.y),-points[i][j+1].z+(this->reference_point.z));
                    glVertex3f(points[i+1][j+1].x+(this->reference_point.x),points[i+1][j+1].y+(this->reference_point.y),-points[i+1][j+1].z+(this->reference_point.z));
                    glVertex3f(points[i+1][j].x+(this->reference_point.x),points[i+1][j].y+(this->reference_point.y),-points[i+1][j].z+(this->reference_point.z));
                }glEnd();
            }
        }
    }
    vect getNormal(point intersectionPoint)
    {
        //vect tmp = {intersectionPoint.x - reference_point.x,intersectionPoint.y - reference_point.y,intersectionPoint.z - reference_point.z};
        
        vect tmp = vectSum(pointToVector(intersectionPoint),scaleVector(reference_point,-1));

        return normalizeVector(tmp);
    }
    void setEta(double val){
        this->eta = val;
    }
    vect getRefraction(vect normal,vect dirVector)
    {
        double cosI = -dotProduct(dirVector,normal);

        double sinT2 = eta*eta*(1.0-cosI*cosI);

        if(GT(sinT2,1.0)){
            //total internal reflection
            return {0,0,0};
        }

        double cosT = sqrt(1.0-sinT2);

        return normalizeVector(vectSum(scaleVector(dirVector,eta),scaleVector(normal,eta*cosI-cosT)));
    }
    double getIntersectingT(LightRay* r)
    {

        double a = dotProduct(r->dir,r->dir);

        vect ro = vectSum({r->start.x,r->start.y,r->start.z},scaleVector({this->reference_point.x,this->reference_point.y,this->reference_point.z},-1));

        //cout<<ro.x<<" "<<ro.y<<" "<<ro.z<<endl;

        double b = 2.0*dotProduct(r->dir,ro);

        double c = dotProduct(ro,ro) - length*length;

        double d = b*b - 4*a*c;

       // cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
        if(LT(d,0))return -1;
        d = sqrt(d);

        double t1 = (-b+d)/(2.0*a);
        double t2 = (-b-d)/(2.0*a);
        return min(t1,t2);
    }
    double  intersect(LightRay *r, double colorAt[3], int level)
     {
        double minT = getIntersectingT(r);
        if(LT(minT,0.0)||EQ(minT,0.0))
            return -1;

        
        point intersectionPoint = movePointAlongvect(r->start,r->dir,minT);

        //cout<<minT<<endl;

        //getColor ---> color
        //setColor ---> this loop
        for(int i=0;i<3;i++){
            colorAt[i] = color[i]*coeffs[AMBIENT];
        }
        if(level==0){
            return minT;
        }
        vect normal = getNormal(intersectionPoint);
        vect reflection = getReflection(normal,r->dir);
        vect refraction = getRefraction(normal,r->dir);

        for(int i=0;i<lights.size();i++){

            vect dirVector = vectSum(lights[i],scaleVector(pointToVector(intersectionPoint),-1.0));
            
            double maxDistanceFromObjecttoLightSource = vectorLength(dirVector);
            
            dirVector = normalizeVector(dirVector);

            point startPoint = movePointAlongvect(intersectionPoint,dirVector,1.0);

            LightRay* tmpRay = new LightRay(startPoint,dirVector);

            bool obscured=false;
            
            for (int j=0;j<objects.size();j++){
                double tmp = objects[j]->getIntersectingT(tmpRay);

                if(GT(tmp,0) && LT(tmp,maxDistanceFromObjecttoLightSource)){//obscured
                    obscured = true;
                    break;
                }

                //not obscured
            }

            if(!obscured){
                //apply phong modeling
                //cout<<"IN: "<<colorAt[0]<<" "<<colorAt[1]<<" "<<colorAt[2]<<endl;
                

                double lambertValue = max(0.0,dotProduct(tmpRay->dir,normal));
                double phongValue = max(pow(dotProduct(r->dir,reflection),shine),0.0);

                //cout<<"lambert and phong: "<<level<<": ";

               // cout<<lambertValue<<" "<<phongValue<<endl;

                double tmp_diffuse = lambertValue*coeffs[DIFFUSE];
                double tmp_speculr = phongValue*coeffs[SPECULR];

                //cout<<tmp_diffuse<<" "<<tmp_speculr<<endl;

                double added = tmp_diffuse + tmp_speculr;

                //cout<<added<<endl;
                
                for(int ii=0;ii<3;ii++){
                    if(added>0){
                       // cout<<"Before: "<<colorAt[ii]<<endl;
                        double asdf=(color[ii]*source_factor)*added;
                        colorAt[ii]+=asdf;
                        //cout<<"After: "<<colorAt[ii]<<endl;
                    }
                }

                
                //cout<<"OUT: "<<colorAt[0]<<" "<<colorAt[1]<<" "<<colorAt[2]<<endl;
            }

            if(level<recursion_level){

                //reflection
                point startPoint = movePointAlongvect(intersectionPoint,reflection,1.0);

                LightRay* reflectedRay = new LightRay(startPoint,reflection);

                int nearest=-1;
                double t_min = INF;
                double *reflectColor=new double[3];

                for(int j=0;j<objects.size();j++){
                    double t = objects[j]->getIntersectingT(reflectedRay);

                    if(LT(t,0)||EQ(t,0))
                        continue;
                    else if(LT(t,t_min)){
                        t_min=t;
                        nearest = j;
                    }
                }

                if(nearest!=-1){
                    objects[nearest]->intersect(reflectedRay,reflectColor,level+1);
                    for(int j=0;j<3;j++){
                        colorAt[j]+=reflectColor[j]*coeffs[REFLECT];
                        
                        // colorAt[j]=min(1.0,colorAt[j]);
                        // colorAt[j]=max(0.0,colorAt[j]);
                    }
                }



                //refraction
                startPoint = movePointAlongvect(intersectionPoint,refraction,1.0);

                LightRay* refractedRay = new LightRay(startPoint,refraction);

                nearest=-1;
                t_min = INF;
                double *refractedColor = new double[3];

                for(int j=0;j<objects.size();j++){
                    double t = objects[j]->getIntersectingT(refractedRay);

                    if(LT(t,0)||EQ(t,0))
                        continue;
                    else if(LT(t,t_min)){
                        t_min=t;
                        nearest = j;
                    }
                }

                if(nearest!=-1){
                    objects[nearest]->intersect(refractedRay,refractedColor,level+1);
                    for(int j=0;j<3;j++){
                        colorAt[j]+=refractedColor[j]*eta;
                        
                        // colorAt[j]=min(1.0,colorAt[j]);
                        // colorAt[j]=max(0.0,colorAt[j]);
                    }
                }
            }
        }



        return minT;
    }
};

class Floor:public BaseObject{
public:
    bitmap_image txt_img;
    double hMul,wMul,floorWidth;
    bool textureAvailable=false;
    
    Floor(double floorWidth,double tileWidth)
    {
        this->reference_point = {-floorWidth/2.0,-floorWidth/2.0,0};
        this->length = tileWidth;

        this->floorWidth =floorWidth;
    }

    void draw(){
        int totalTiles = fabs(this->reference_point.x*2.0)/(this->length);
        
        if(!colorSet){
            color[0]=1;
            color[1]=1;
            color[2]=1;
        }

        for(int i=0;i<totalTiles;i++){
            for(int j=0;j<totalTiles;j++){
                
                if((i+j)%2){
                    glColor3f(color[0],color[1],color[2]);
                }
                else
                    glColor3f(0,0,0);

                glBegin(GL_QUADS);
                {
                    glVertex3f(reference_point.x+length*i, reference_point.y+length*j, reference_point.z);
                    glVertex3f(reference_point.x+length*(i+1), reference_point.y+length*j, reference_point.z);
                    glVertex3f(reference_point.x+length*(i+1), reference_point.y+length*(j+1), reference_point.z);
                    glVertex3f(reference_point.x+length*i, reference_point.y+length*(j+1), reference_point.z);
                }
                glEnd();
            }
        }
    }

    void setTextureFile(string fileName)
    {
    	this->txt_img = bitmap_image(fileName);
        this->hMul = (1.0*txt_img.height())/floorWidth;
        this->wMul = (1.0*txt_img.width())/floorWidth;
    	this->textureAvailable = true;
    }

    vect getNormal(point intersectionPoint)
    {
        vect tmp = {0,0,1};
        return tmp;
    }

    double getIntersectingT(LightRay* r)
    {
        vect normal = getNormal({0,0,0}); //dummyvalue

        //the plane goes through the origin, so in Ax+By+Cz+D = 0, D = 0

        double t = -1.0*dotProduct(normal,pointToVector(r->start)) / dotProduct(r->dir,normal);
        return t;
    }

    double  intersect(LightRay *r, double colorAt[3], int level)
    {

        double minT = getIntersectingT(r);
        point intersectionPoint = movePointAlongvect(r->start,r->dir,minT);

        double minX = reference_point.x;
        double maxX = -reference_point.x;
        double minY = reference_point.y;
        double maxY = -reference_point.y;

        if(intersectionPoint.x < minX|| intersectionPoint.y < minY|| intersectionPoint.x > maxX || intersectionPoint.y >maxY)//outside the valid region
            return -1;

        if(level==0)
            return minT;


        int tileX = (intersectionPoint.x - reference_point.x)/length;
        int tileY = (intersectionPoint.y - reference_point.y)/length;


        if((tileX+tileY)%2){
            double tmp=color[0];
            if(!colorSet)
                tmp=1;
            color[0]=color[1]=color[2]=tmp;
        }
        else
            color[0]=color[1]=color[2]=0;
        

        for(int i=0;i<3;i++)
            colorAt[i] = color[i]*coeffs[AMBIENT];
        

        if(this->textureAvailable){
	        unsigned char rr,gg,bb;

	        int tx = (intersectionPoint.x+fabs(reference_point.x))*wMul;
	        int ty = (intersectionPoint.y+fabs(reference_point.y))*hMul;

	        txt_img.get_pixel(tx,ty,rr,gg,bb);

	        double txt_color[] = {1.0*rr,1.0*gg,1.0*bb};

	        for(int i=0;i<3;i++)
	            colorAt[i] = colorAt[i]*(1.0*txt_color[i]/255.0);
	    }

        vect normal = getNormal(intersectionPoint);

        vect reflection = getReflection(normal,r->dir);


        for(int i=0;i<lights.size();i++){

            vect dirVector = vectSum(lights[i],scaleVector(pointToVector(intersectionPoint),-1.0));
            
            double maxDistanceFromObjecttoLightSource = vectorLength(dirVector);
            
            dirVector = normalizeVector(dirVector);

            point startPoint = movePointAlongvect(intersectionPoint,dirVector,1.0);

            LightRay* tmpRay = new LightRay(startPoint,dirVector);

            bool obscured=false;
            
            for (int j=0;j<objects.size();j++){
                double tmp = objects[j]->getIntersectingT(tmpRay);

                if(GT(tmp,0) && LT(tmp,maxDistanceFromObjecttoLightSource)){//obscured
                    obscured = true;
                    break;
                }

                //not obscured
            }

            if(!obscured){
                //apply phong modeling
                //cout<<"IN: "<<colorAt[0]<<" "<<colorAt[1]<<" "<<colorAt[2]<<endl;
                double lambertValue = max(0.0,dotProduct(tmpRay->dir,normal));
                double phongValue = max(pow(dotProduct(r->dir,reflection),shine),0.0);

                //cout<<"lambert and phong: "<<level<<": ";

               // cout<<lambertValue<<" "<<phongValue<<endl;

                double tmp_diffuse = lambertValue*coeffs[DIFFUSE];
                double tmp_speculr = phongValue*coeffs[SPECULR];

                //cout<<tmp_diffuse<<" "<<tmp_speculr<<endl;

                double added = tmp_diffuse + tmp_speculr;

                //cout<<added<<endl;

                
                for(int ii=0;ii<3;ii++){
                    if(added>0){
                       // cout<<"Before: "<<colorAt[ii]<<endl;
                        colorAt[ii]+= (color[ii] *source_factor)*added;
                        //cout<<"After: "<<colorAt[ii]<<endl;
                    }
                }

                
                //cout<<"OUT: "<<colorAt[0]<<" "<<colorAt[1]<<" "<<colorAt[2]<<endl;
            }

            if(level<recursion_level){

                point startPoint = movePointAlongvect(intersectionPoint,reflection,1.0);

                LightRay* reflectedRay = new LightRay(startPoint,reflection);

                int nearest=-1;
                double t_min = INF;
                double *reflectColor = new double[3];

                for(int j=0;j<objects.size();j++){
                    double t = objects[j]->getIntersectingT(reflectedRay);

                    if(LT(t,0)||EQ(t,0))
                        continue;
                    else if(LT(t,t_min)){
                        t_min=t;
                        nearest = j;
                    }
                }

                if(nearest!=-1){
                    objects[nearest]->intersect(reflectedRay,reflectColor,level+1);
                    for(int j=0;j<3;j++){
                        colorAt[j]+=reflectColor[j]*coeffs[REFLECT];
                        
                        colorAt[j]=min(1.0,colorAt[j]);
                        colorAt[j]=max(0.0,colorAt[j]);
                    }
                }

            }
        }
        return minT;
    }
};
class Triangle: public BaseObject{
public:
    point p1,p2,p3;

    Triangle(point a,point b, point c)
    {
        p1=a;p2=b;p3=c;
    }
    void draw(){
        glColor3f(this->color[0],this->color[1],this->color[2]);
        glBegin(GL_TRIANGLES);{
            glVertex3f(p1.x,p1.y,p1.z);
            glVertex3f(p2.x,p2.y,p2.z);
            glVertex3f(p3.x,p3.y,p3.z);
        }glEnd();
    }
    vect getNormal(point intersectionPoint){
        vect a = {p2.x-p1.x,p2.y-p1.y,p2.z-p1.z}; //p2-p1== p1--->p2   
        vect b = {p3.x-p1.x,p3.y-p1.y,p3.z-p1.z}; //p3-p1== p1--->p3
        vect c = crossProduct(a,b);
        return normalizeVector(c);
    }
    double getIntersectingT(LightRay* r)
    {
        const float EPSILON = 0.0000001; 

        vect edge1 = {p2.x-p1.x,p2.y-p1.y,p2.z-p1.z}; 
        vect edge2 = {p3.x-p1.x,p3.y-p1.y,p3.z-p1.z}; 


        vect h = crossProduct(r->dir,edge2);

        double a = dotProduct(edge1,h);

        if(GT(a , -EPSILON) && LT(a , EPSILON))
            return -1;

        double f = 1.0/a;

        vect s = {r->start.x-p1.x,r->start.y-p1.y,r->start.z-p1.z};

        double u = f*dotProduct(s,h);

        if(LT(u,0.0)||GT(u,1.0))
            return -1;

        vect q = crossProduct(s,edge1);

        double v = f*dotProduct(r->dir,q);

        if(LT(v,0.0)||GT(u+v,1.0))
            return -1;

        double t =  f*dotProduct(edge2,q);

        if(GT(t,EPSILON))
            return t;
        return -1;

    }
    double  intersect(LightRay *r, double colorAt[3], int level){
        double minT = getIntersectingT(r);

        if(LT(minT,0.0)||EQ(minT,0.0))
            return -1;

        if(level==0)
            return minT;


        point intersectionPoint = movePointAlongvect(r->start,r->dir,minT);

        //getColor ---> color
        //setColor ---> this loop
        for(int i=0;i<3;i++)
            colorAt[i] = color[i]*coeffs[AMBIENT];

        vect normal = getNormal(intersectionPoint);
        vect reflection = getReflection(normal,r->dir);

        for(int i=0;i<lights.size();i++){

            vect dirVector = vectSum(lights[i],scaleVector(pointToVector(intersectionPoint),-1.0));
            
            double maxDistanceFromObjecttoLightSource = vectorLength(dirVector);
            
            dirVector = normalizeVector(dirVector);

            point startPoint = movePointAlongvect(intersectionPoint,dirVector,1.0);

            LightRay* tmpRay = new LightRay(startPoint,dirVector);

            bool obscured=false;
            
            for (int j=0;j<objects.size();j++){
                double tmp = objects[j]->getIntersectingT(tmpRay);

                if(GT(tmp,0) && LT(tmp,maxDistanceFromObjecttoLightSource)){//obscured
                    obscured = true;
                    break;
                }

                //not obscured
            }

            if(!obscured){
                //apply phong modeling
                //cout<<"IN: "<<colorAt[0]<<" "<<colorAt[1]<<" "<<colorAt[2]<<endl;
                double lambertValue = max(0.0,dotProduct(tmpRay->dir,normal));
                double phongValue = max(pow(dotProduct(r->dir,reflection),shine),0.0);

                //cout<<"lambert and phong: "<<level<<": ";

               // cout<<lambertValue<<" "<<phongValue<<endl;

                double tmp_diffuse = lambertValue*coeffs[DIFFUSE];
                double tmp_speculr = phongValue*coeffs[SPECULR];

                //cout<<tmp_diffuse<<" "<<tmp_speculr<<endl;

                double added = tmp_diffuse + tmp_speculr;

                //cout<<added<<endl;

                
                for(int ii=0;ii<3;ii++){
                    if(added>0){
                       // cout<<"Before: "<<colorAt[ii]<<endl;
                        colorAt[ii]+= (color[ii] *source_factor)*added;
                        //cout<<"After: "<<colorAt[ii]<<endl;
                    }
                }

                
                //cout<<"OUT: "<<colorAt[0]<<" "<<colorAt[1]<<" "<<colorAt[2]<<endl;
            }

            if(level<recursion_level){

                point startPoint = movePointAlongvect(intersectionPoint,reflection,1.0);

                LightRay* reflectedRay = new LightRay(startPoint,reflection);

                int nearest=-1;
                double t_min = INF;
                double *reflectColor=new double[3];

                for(int j=0;j<objects.size();j++){
                    double t = objects[j]->getIntersectingT(reflectedRay);

                    if(LT(t,0)||EQ(t,0))
                        continue;
                    else if(LT(t,t_min)){
                        t_min=t;
                        nearest = j;
                    }
                }

                if(nearest!=-1){
                    objects[nearest]->intersect(reflectedRay,reflectColor,level+1);
                    for(int j=0;j<3;j++){
                        colorAt[j]+=reflectColor[j]*coeffs[REFLECT];
                        
                        colorAt[j]=min(1.0,colorAt[j]);
                        colorAt[j]=max(0.0,colorAt[j]);
                    }
                }

            }
        }
        return minT;
    }
};

class GenericQuad:public BaseObject{
public:
    double A,B,C,D,E,F,G,H,I,J;
    GenericQuad(double  A,double  B,double  C,double  D,double  E,double  F,double  G,double  H,double  I,double  J,point reference_point,double length,double width,double height)
    {
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
        this->E = E;
        this->F = F;
        this->G = G;
        this->H = H;
        this->I = I;
        this->J = J;

        this->reference_point = pointToVector(reference_point);
        this->length = length;
        this->width = width;
        this->height = height;
    }
    void draw(){
        glColor3f(color[0],color[1],color[2]);
        
        glPointSize(7);
        
        glBegin(GL_POINTS);
        {
            glVertex3f(reference_point.x,reference_point.y,reference_point.z);
        }
        glEnd();
    }
    vect getNormal(point intersectionPoint){
        double df_dx = 2.0*A*intersectionPoint.x+D*intersectionPoint.y+E*intersectionPoint.z+G;
        double df_dy = 2.0*B*intersectionPoint.y+D*intersectionPoint.x+F*intersectionPoint.z+H;
        double df_dz = 2.0*C*intersectionPoint.z+E*intersectionPoint.x+F*intersectionPoint.z+I;

        vect v = {df_dx,df_dy,df_dz};

        return normalizeVector(v);
    }
    bool isInsideLimit(point p1,point pMin,point  pMax)
    {
        return (GT(length,0) && GTE(p1.x,pMin.x) && LTE(p1.x,pMax.x))||(GT(width,0)&&GTE(p1.y,pMin.y) && LTE(p1.y,pMax.y))||(GT(height,0)&&GTE(p1.z,pMin.z) && LTE(p1.z,pMax.z));
    }
    double getIntersectingT(LightRay* r)
    {
        vect d = r->dir;
        point o = r->start;

        double a = (A*d.x*d.x) + (B*d.y*d.y) + (C*d.z*d.z) + (D*d.x*d.y) + (E*d.x*d.z) + (F*d.z*d.y);
        double b = (2.0*A*o.x*d.x)+(2.0*B*o.y*d.y)+(2.0*C*o.z*d.z)+(1.0*D*(o.x*d.y+d.x*o.y))+(1.0*E*(o.z*d.x+o.x*d.z))+(1.0*F*(o.z*d.y+d.z*o.y))+(G*d.x)+(H*d.y)+(I*d.z);
        double c = (A*o.x*o.x)+(B*o.y*o.y)+(C*o.z*o.z)+(D*o.x*o.y)+(E*o.x*o.z)+(F*o.z*o.y)+(G*o.x)+(H*o.y)+(I*o.z)+J;

        //cout<<a<<" "<<b<<" "<<c<<endl;
        double D = b*b - 4*a*c;
        if(D<0)return  -1;
        D = sqrt(D);

        double t1 = (-b+D)/(2.0*a);
        double t2 = (-b-D)/(2.0*a);


        point ip1 = movePointAlongvect(r->start,r->dir,t1);
        point ip2 = movePointAlongvect(r->start,r->dir,t2);

        double minX = reference_point.x;
        double maxX = reference_point.x+length;
        
        double minY = reference_point.y;
        double maxY = reference_point.y+width;
        
        double minZ = reference_point.z;
        double maxZ = reference_point.z+height;

        if(isInsideLimit(ip1,{minX,minY,minZ},{maxX,maxY,maxZ})&&isInsideLimit(ip2,{minX,minY,minZ},{maxX,maxY,maxZ})){
            return min(t1,t2);
        }
        else if(isInsideLimit(ip1,{minX,minY,minZ},{maxX,maxY,maxZ})){
            return  t1;
        }
        else if(isInsideLimit(ip2,{minX,minY,minZ},{maxX,maxY,maxZ})){
            return t2;
        }
        else 
            return -1;
    }
    double  intersect(LightRay *r, double colorAt[3], int level){
        
        double minT = getIntersectingT(r);
        //cout<<minT<<endl;
        if(LT(minT,0.0)||EQ(minT,0.0))
            return -1;

        if(level==0)
            return minT;
        point intersectionPoint = movePointAlongvect(r->start,r->dir,minT);
        //getColor ---> color
        //setColor ---> this loop
        for(int i=0;i<3;i++)
            colorAt[i] = color[i]*coeffs[AMBIENT];
        vect normal = getNormal(intersectionPoint);
        vect reflection = getReflection(normal,r->dir);

        for(int i=0;i<lights.size();i++){

            vect dirVector = vectSum(lights[i],scaleVector(pointToVector(intersectionPoint),-1.0));
            
            double maxDistanceFromObjecttoLightSource = vectorLength(dirVector);
            
            dirVector = normalizeVector(dirVector);

            point startPoint = movePointAlongvect(intersectionPoint,dirVector,1.0);

            LightRay* tmpRay = new LightRay(startPoint,dirVector);

            bool obscured=false;
            
            for (int j=0;j<objects.size();j++){
                double tmp = objects[j]->getIntersectingT(tmpRay);

                if(GT(tmp,0) && LT(tmp,maxDistanceFromObjecttoLightSource)){//obscured
                    obscured = true;
                    break;
                }

                //not obscured
            }

            if(!obscured){
                //apply phong modeling
                //cout<<"IN: "<<colorAt[0]<<" "<<colorAt[1]<<" "<<colorAt[2]<<endl;
                

                double lambertValue = max(0.0,dotProduct(tmpRay->dir,normal));
                double phongValue = max(pow(dotProduct(r->dir,reflection),shine),0.0);

                //cout<<"lambert and phong: "<<level<<": ";

               // cout<<lambertValue<<" "<<phongValue<<endl;

                double tmp_diffuse = lambertValue*coeffs[DIFFUSE];
                double tmp_speculr = phongValue*coeffs[SPECULR];

                //cout<<tmp_diffuse<<" "<<tmp_speculr<<endl;

                double added = tmp_diffuse + tmp_speculr;

                //cout<<added<<endl;

                
                for(int ii=0;ii<3;ii++){
                    if(added>0){
                       // cout<<"Before: "<<colorAt[ii]<<endl;
                        colorAt[ii]+= (color[ii] *source_factor)*added;
                        //cout<<"After: "<<colorAt[ii]<<endl;
                    }
                }

                
                //cout<<"OUT: "<<colorAt[0]<<" "<<colorAt[1]<<" "<<colorAt[2]<<endl;
            }

            if(level<recursion_level){

                point startPoint = movePointAlongvect(intersectionPoint,reflection,1.0);

                LightRay* reflectedRay = new LightRay(startPoint,reflection);

                int nearest=-1;
                double t_min = INF;
                double *reflectColor=new double[3];

                for(int j=0;j<objects.size();j++){
                    double t = objects[j]->getIntersectingT(reflectedRay);

                    if(LT(t,0)||EQ(t,0))
                        continue;
                    else if(LT(t,t_min)){
                        t_min=t;
                        nearest = j;
                    }
                }

                if(nearest!=-1){
                    objects[nearest]->intersect(reflectedRay,reflectColor,level+1);
                    for(int j=0;j<3;j++){
                        colorAt[j]+=reflectColor[j]*coeffs[REFLECT];
                        
                        colorAt[j]=min(1.0,colorAt[j]);
                        colorAt[j]=max(0.0,colorAt[j]);
                    }
                }

            }
        }
        return minT;
    }
};