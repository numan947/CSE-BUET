#include<math.h>
#define pi (2*acos(0.0))

#define AMBIENT 0
#define DIFFUSE 1
#define SPECULR 2
#define REFLECT 3


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
    double height,width,length,source_factor = 1.0,eta = 1.5;
    int shine;
    double color[3];
    double coeffs[4];
    bool colorSet;

    BaseObject(){}

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

    void setEta(double val)
    {
        this->eta = val;
    }

};


extern int recursion_level;
extern vector<vect>lights;
extern vector<BaseObject*>objects;


class Sphere: public BaseObject{
public:
    Sphere(point center,double radius){
        this->reference_point = {center.x,center.y,center.z};
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
        for(i=0;i<=stacks;i++)
        {
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
        for(i=0;i<stacks;i++)
        {
            //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            for(j=0;j<slices;j++)
            {
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
        vect tmp = {intersectionPoint.x - reference_point.x,intersectionPoint.y - reference_point.y,intersectionPoint.z - reference_point.z};
        return normalizeVector(tmp);
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

        if(d<0)return -1;


        d = sqrt(d);

        double t1 = (-b+d)/(2.0*a);
        double t2 = (-b-d)/(2.0*a);

        return min(t1,t2);
    }



     double  intersect(LightRay *r, double colorAt[3], int level)
     {

        double minT = getIntersectingT(r);
        
        if(minT<=0)
            return -1;

        if(level==0){
            return minT;
        }


        point intersectionPoint = movePointAlongvect(r->start,r->dir,minT);

        //getColor ---> color
        //setColor ---> this loop
        for(int i=0;i<3;i++)
            colorAt[i] = color[i]*coeffs[AMBIENT];

        vect normal = getNormal(intersectionPoint);

        vect reflection = getReflection(normal,r->dir);

        for(int i=0;i<lights.size();i++){

            vect dirVector = vectSum(lights[i],scaleVector({intersectionPoint.x,intersectionPoint.y,intersectionPoint.z},-1.0));
            
            double maxDistanceFromObjecttoLightSource = sqrt(dirVector.x*dirVector.x+dirVector.y*dirVector.y+dirVector.z*dirVector.z);
            
            dirVector = normalizeVector(dirVector);

            point startPoint = movePointAlongvect(intersectionPoint,dirVector,1.0);

            LightRay* tmpRay = new LightRay(startPoint,dirVector);

            bool obscured=false;
            
            for (int j=0;j<objects.size();j++){
                double tmp = objects[i]->getIntersectingT(tmpRay);

                if(tmp>0 && tmp<maxDistanceFromObjecttoLightSource){//obscured
                    obscured = true;
                    break;
                }

                //not obscured
            }

            if(!obscured){
                //apply phong modeling
                double lambertValue = dotProduct(tmpRay->dir,normal);
                double phongValue = pow(dotProduct(r->dir,reflection),shine);

                for(int ii=0;ii<3;ii++)
                    colorAt[ii]+= (this->color[ii] * this->source_factor) *
                                                    (lambertValue*(this->coeffs[DIFFUSE]) + 
                                                        phongValue*(this->coeffs[SPECULR]));
            }

            if(level<recursion_level){

                point startPoint = movePointAlongvect(intersectionPoint,reflection,1.0);

                LightRay* reflectedRay = new LightRay(startPoint,reflection);

                int nearest=-1;
                double t_min = INF;
                double reflectColor[3];

                for(int j=0;j<objects.size();j++){
                    double t = objects[j]->getIntersectingT(reflectedRay);

                    if(t<=0)
                        continue;
                    else if(t<t_min){
                        t_min=t;
                        nearest = j;
                    }
                }

                if(nearest!=-1){
                    objects[nearest]->intersect(reflectedRay,reflectColor,level+1);
                    for(int j=0;j<3;j++)
                        colorAt[j]+=reflectColor[j]*coeffs[REFLECT];
                }

            }



        }



        return minT;





     }












};





class Floor:public BaseObject{
public:
    
    Floor(double floorWidth,double tileWidth)
    {
        this->reference_point = {-floorWidth/2.0,-floorWidth/2.0};
        this->length = tileWidth;
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
};