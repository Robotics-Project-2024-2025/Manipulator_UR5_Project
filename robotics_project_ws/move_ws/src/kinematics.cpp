//
//  kinematics.cpp
//  Kinematics
//
//  Created by Matteo Gottardelli on 21/11/24.
//

#include "kinematics.h"
vector<double> A={0, -0.425, -0.3922, 0, 0, 0};
vector<double> D={0.1625, 0, 0, 0.1333, 0.0997, 0.0996};
vector<double> alfa={M_PI/2, 0, 0, M_PI/2, -M_PI/2, 0};

float adjust_value(float x) {
    if(x<1e-6 && x>-1e-6) {
        return 0;
    }
    return x;
}
float adjust_asin(float x) {
    if(x<-1) {
        return -M_PI/2;
    }
    if(x>1) {
        return M_PI/2;
    }
    return asin(x);
}
float adjust_acos(float x) {
    if(x<-1) {
        return M_PI;
    }
    if(x>1) {
        return 0;
    }
    return acos(x);
}
Matrix3d eul2rotm(Vector3d phiEf) {
    return zRot(phiEf(0)) * yRot(phiEf(1)) * xRot(phiEf(2));
}
// Source of the pseudocode: https://www.geometrictools.com/Documentation/EulerAngles.pdf
Vector3d rotm2eul(Matrix3d m) {
    double x, y, z;
    if(m(2,0)<1) {
        if(m(2,0)>-1) {
            x=atan2(m(2,1), m(2,2));
            y=adjust_asin(-m(2,0));
            z=atan2(m(1,0), m(0,0));
        }
        else {
            x=0;
            y=M_PI/2;
            z=-atan2(-m(1,2), m(1,1));
        }
    }
    else {
        x=0;
        y=-M_PI/2;
        z=-atan2(-m(1,2), m(1,1));
    }
    Vector3d ret;
    ret << z, y, x;
    return ret;
}
void removeRow(MatrixD6* m, unsigned int remove) {
    unsigned long int numRows = m->rows()-1;
    unsigned long int numCols = m->cols();
    if( remove < numRows ) {
        m->block(remove,0,numRows-remove,numCols) = m->block(remove+1,0,numRows-remove,numCols);
    }
    m->conservativeResize(numRows,numCols);
}
//J(theta)=sum_0_7(theta_end-theta_start)^2
bool bestInverse(Matrix16 start, MatrixD6& end) {
    //Too much rotation of the base
    for (int i=0; i<end.rows(); i++) {
        if(end(i,0)>M_PI) {
            end(i,0)=end(i,0)-2*M_PI;
        }
        else {
            if (end(i,0)<-M_PI) {
                end(i,0)=end(i,0)+2*M_PI;
            }
        }
    }
    int i=0;
    while (i<end.rows()){
        Matrix16 thi=end.row(i);
        if (!checkAngles(thi)){
            removeRow(&end, i);
            cout << "Row " << i << " REMOVED" << endl;
        } else {
            i++;
        }
    }
    double configs[end.rows()];
    for (int i=0; i<end.rows(); i++) {
        configs[i]=0.0;
        for (int j=0; j<NUM_JOINTS; j++) {
            configs[i]+=pow(end(i, j)-start(j), 2);
        }
    }
    for (int i=0; i<end.rows()-1; i++) {
        Matrix16 thi=end.row(i);
        for (int j=i+1; j<end.rows(); j++) {
            Matrix16 thj=end.row(j);
            if(configs[j]<configs[i]) {
                end.row(j)=thi;
                end.row(i)=thj;
            }
        }
    }
    if (end.size()==0) {
        cout << "NO POSSIBLE ERROR TRAJECTORY" << endl;
        return false;
    }
    return true;
}
bool control_collision(Matrix16 th) {
    MatrixD4 matrices[NUM_JOINTS];
    for (int i=0; i<NUM_JOINTS; i++) {
        matrices[i]=HomogeneousTransformSpecific(i, th[i]);
    }
    Matrix4d Id;
    Id << 1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1;
    for (int i=0; i<NUM_JOINTS; i++) {
        Id=Id*matrices[i];
        double pos_x = Id(0,3);
        double pos_y = Id(1,3);
        double pos_z = Id(2,3);
        if(pos_x<XMIN || pos_x>XMAX) {
            cout << "COLLISION X: " << pos_x << " " << XMIN << " " << XMAX << " " << i+1 << endl;
            return false;
        }
        if(pos_y<YMIN || pos_y>YMAX(i)) {
            cout << "COLLISION Y: " << pos_y << " " << YMIN << " " << YMAX << " " << i+1 << endl;
            return false;
        }
        if(pos_z < ZMIN || pos_z>ZMAX) {
            cout << "COLLISION Z: " << pos_z << " " << ZMIN << " " << ZMAX << " " << i+1 << endl;
            return false;
        }
    }
    return true;
    
}
bool checkAngles(Matrix16 th) {
    bool ret=true;
    //Check Limits
    RowVector2d J1{-2*M_PI, 2*M_PI};
    RowVector2d J2{-M_PI, 0};
    RowVector2d J3{-M_PI, M_PI};
    RowVector2d J4{-2*M_PI, 2*M_PI};
    RowVector2d J5{-2*M_PI, 2*M_PI};
    RowVector2d J6{-2*M_PI, 2*M_PI};
    RowVector2d AllJ[NUM_JOINTS]={J1, J2, J3, J4, J5, J6};
    for (int i=0; i<NUM_JOINTS && ret; i++) {
        if(!(th[i]>AllJ[i][0] && th[i]<AllJ[i][1])) {
            cout << "ERROR ANGLES " << th[i] << "   " << i+1 << " " << AllJ[i][0] << "-" << AllJ[i][1] << endl;
            ret=false;
        }
    }
    //Check collision
    if (ret) {
        if(!control_collision(th)) {
            ret=false;
        }
    }
    return ret;
}

bool p2pMotionPlan(Matrix61 qES, Vector3d xEf, Vector3d phiEf, MatrixD6* Th) {
    MatrixXd xE;
    MatrixXd phiE;
     //Matrix86 qES = Ur5Inverse(xEs, eul2rotm(phiEs));
     MatrixD6 qEF = Ur5Inverse(xEf, eul2rotm(phiEf));
    if(!bestInverse(qES, qEF)) {
        return false;
    }
    cout << qEF << endl;
     //VectorXd qEf = qEF.row(index);
    for (int i = 0; i < qEF.rows(); ++i) {
        MatrixD6 A;
        bool error=false;
        for (int j=0; j<qES.rows(); j++) {
            MatrixXd M(6, 6);
            M << 1, MINT, pow(MINT, 2), pow(MINT, 3), pow(MINT, 4), pow(MINT, 5),
            0, 1, 2 * MINT, 3 * pow(MINT, 2), 4 * pow(MINT, 3), 5 * pow(MINT, 4),
            0, 0, 2, 6 * MINT, 12 * pow(MINT, 2), 20 * pow(MINT, 3),
            1, MAXT, pow(MAXT, 2), pow(MAXT, 3), pow(MAXT, 4), pow(MAXT, 5),
            0, 1, 2 * MAXT, 3 * pow(MAXT, 2), 4 * pow(MAXT, 3), 5 * pow(MAXT, 4),
            0, 0, 2, 6 * MAXT, 12 * pow(MAXT, 2), 20 * pow(MAXT, 3);
            VectorXd b(6);
            b << qES(j), 0, 0, qEF(i, j), 0, 0;
            MatrixXd M_inv = M.inverse();
            VectorXd coeff = M_inv*b;
            A.conservativeResize(A.rows()+1, Eigen::NoChange);
            A.row(A.rows()-1) = coeff.transpose();
        }
        for (double t = MINT; t<MAXT+DELTAT; t+=DELTAT) {
            VectorXd th(NUM_JOINTS);
            for (int k = 0; k < qES.rows(); k++) {
                th(k)=A(k, 0) + A(k, 1) * t + A(k, 2) * pow(t, 2) + A(k, 3) * pow(t, 3) + A(k, 4) * pow(t, 4) + A(k, 5) * pow(t, 5);
            }
            //CHECK ANGLES
            if (!checkAngles(th)) {
                cout << "TRAJECTORY ERROR" << endl;
                error=true;
            }
            Th->conservativeResize(Th->rows() + 1, NUM_JOINTS);
            Th->row(Th->rows()-1)=th;
            //Matrix61 m61 = Th.row(Th.rows()-1);
            /*pair<Vector3d, Matrix3d> pa = Ur5Direct(m61);
            xE.conservativeResize(xE.rows() + 1, 3);
            xE.row(xE.rows()-1)=(get<0>(pa)).transpose();
            phiE.conservativeResize(phiE.rows() + 1, 3);
            phiE.row(phiE.rows() - 1) = rotm2eul(get<1>(pa));*/
        }
        if(!error) {
            return true;
        }
    }
    return false;
}

Matrix3d xRot(double theta){
    Matrix3d r;
    r << 1, 0, 0,
         0, cos(theta), -sin(theta),
         0,sin(theta),cos(theta);
    return r;
}

Matrix3d yRot(double theta){
    Matrix3d r;
    r << cos(theta), 0, sin(theta),
         0, 1, 0,
         -sin(theta),0,cos(theta);
    return r;
}

Matrix3d zRot(double theta){
    Matrix3d r;
    r << cos(theta), -sin(theta), 0,
          sin(theta), cos(theta), 0,
          0,0,1;
    return r;
}
Matrix44 HomogeneousTransformGen(int i, double theta, double alpha, double d, double a){
    Matrix44 m;
    m << adjust_value(cos(theta)), adjust_value(-sin(theta)*cos(alpha)), adjust_value(sin(theta)*sin(alpha)), a*adjust_value(cos(theta)),
    adjust_value(sin(theta)), adjust_value(cos(theta)*cos(alpha)), adjust_value(-cos(theta)*sin(alpha)), a*adjust_value(sin(theta)),
    0, adjust_value(sin(alpha)), adjust_value(cos(alpha)), d,
    0,0,0,1;
    return m;
}
Matrix44 HomogeneousTransformSpecific(int i, double theta) {
    Matrix44 retM;
    switch (i) {
        case 0:
            retM << adjust_value(cos(theta)), adjust_value(-sin(theta)), 0, 0,
            adjust_value(sin(theta)), adjust_value(cos(theta)), 0, 0,
                    0, 0, 1, D[0],
                    0, 0, 0, 1;
            break;
        case 1:
            retM << adjust_value(cos(theta)), adjust_value(-sin(theta)), 0, 0,
                    0, 0, -1, 0,
            adjust_value(sin(theta)), adjust_value(cos(theta)), 0, 0,
                    0, 0, 0, 1;
            break;
        case 2:
            retM << adjust_value(cos(theta)), adjust_value(-sin(theta)), 0, A[1],
            adjust_value(sin(theta)), adjust_value(cos(theta)), 0, 0,
                    0, 0, 1, D[2],
                    0, 0, 0, 1;
            break;
        case 3:
            retM << adjust_value(cos(theta)), adjust_value(-sin(theta)), 0, A[2],
            adjust_value(sin(theta)), adjust_value(cos(theta)), 0, 0,
                    0, 0, 1, D[3],
                    0, 0, 0, 1;
            break;
        case 4:
            retM << adjust_value(cos(theta)), adjust_value(-sin(theta)), 0, 0,
                    0, 0, -1, -D[4],
            adjust_value(sin(theta)), adjust_value(cos(theta)), 0, 0,
                    0, 0, 0, 1;
            break;
        case 5:
            retM << adjust_value(cos(theta)), adjust_value(-sin(theta)), 0, 0,
                    0, 0, 1, D[5],
            adjust_value(-sin(theta)), adjust_value(-cos(theta)), 0, 0,
                    0, 0, 0, 1;
            break;
        default:
            cerr << "Error input Type Homogeneous Specific" << endl;
            exit(1);
            break;
    }
    return retM;
}
pair<Vector3d, Matrix3d> Ur5Direct(Matrix61 Th) {
   
    //T[NUM_JOINTS]={T10, T21, T32, T43, T54, T65}
    Matrix44 T60;
    T60 << 1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1;
    Matrix44 T;
    for (int i=0; i<NUM_JOINTS; i++) {
        T=HomogeneousTransformGen(i, Th[i], alfa[i], D[i], A[i]);
        T60*=T;
    }
    Vector3d v;
    Matrix3d m;
    v << T60(0, 3), T60(1, 3), T60 (2, 3);
    m << T60(0, 0), T60(0, 1), T60(0, 2),
         T60(1, 0), T60(1, 1), T60(1, 2),
         T60(2, 0), T60(2, 1), T60(2, 2);
    return make_pair(v, m);
}

Matrix86 Ur5Inverse(Vector3d v, Matrix3d m){ //vector = punti di destinazione; m= matrice rotazionale
    Matrix44 T60;
    v[1]=-v[1];
    v[2]=-v[2];
    T60 << m(0,0), m(0,1), m(0,2), v(0),
           m(1,0), m(1,1), m(1,2), v(1),
           m(2,0), m(2,1), m(2,2), v(2),
           0,0,0,1;
//th1
    
    Matrix41 tmp;
    tmp << 0,0,-D[5],1;
    Matrix14 p50=T60*tmp;
    double th1_1 = real((atan2(p50(1), p50(0)) + adjust_acos(D[3]/hypot(p50(1), p50(0))))) + M_PI/2;
    double th1_2 = real((atan2(p50(1), p50(0)) - adjust_acos(D[3]/hypot(p50(1), p50(0))))) + M_PI/2;
//th5
    double th5_1 = adjust_acos((v(0)*sin(th1_1) - v(1)*cos(th1_1)-D[3]) / D[5]);
    double th5_2 = -adjust_acos((v(0)*sin(th1_1) - v(1)*cos(th1_1)-D[3]) / D[5]);
    double th5_3 = adjust_acos((v(0)*sin(th1_2) - v(1)*cos(th1_2)-D[3]) / D[5]);
    double th5_4 = -adjust_acos((v(0)*sin(th1_2) - v(1)*cos(th1_2)-D[3]) / D[5]);

//related to th11 a th51
    Matrix44 T06 = T60.inverse();
    vector<double> Xhat = {T06(0,0), T06(1,0), T06(2,0)};
    vector<double> Yhat = {T06(0,1), T06(1,1), T06(2,1)};
    double th6_1 = real(atan2(((-Xhat[1]*sin(th1_1)+Yhat[1]*cos(th1_1)))/sin(th5_1), ((Xhat[0]*sin(th1_1)-Yhat[0]*cos(th1_1)))/sin(th5_1)));
//related to th11 a th52
    double th6_2 = real(atan2(((-Xhat[1]*sin(th1_1)+Yhat[1]*cos(th1_1))/sin(th5_2)), ((Xhat[0]*sin(th1_1)-Yhat[0]*cos(th1_1))/sin(th5_2))));
//related to th12 a th53
    double th6_3 = real(atan2(((-Xhat[1]*sin(th1_2)+Yhat[1]*cos(th1_2))/sin(th5_3)), ((Xhat[0]*sin(th1_2)-Yhat[0]*cos(th1_2))/sin(th5_3))));
//related to th12 a th54
    double th6_4 = real(atan2(((-Xhat[1]*sin(th1_2)+Yhat[1]*cos(th1_2))/sin(th5_4)), ((Xhat[0]*sin(th1_2)-Yhat[0]*cos(th1_2))/sin(th5_4))));



    Matrix44 T41m = ((HomogeneousTransformSpecific(0, th1_1)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_1)).inverse())*((HomogeneousTransformSpecific(4, th5_1)).inverse());
    vector<double> p41_1 = {T41m(0,3), T41m(1,3), T41m(2,3)};
    double p41xz_1 = hypot(p41_1[0], p41_1[2]);
    
    T41m = ((HomogeneousTransformSpecific(0, th1_1)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_2)).inverse())*((HomogeneousTransformSpecific(4, th5_2)).inverse());
   
    vector<double> p41_2 ={T41m(0,3), T41m(1,3), T41m(2,3)};
    double p41xz_2 = hypot(p41_2[0], p41_2[2]);

    T41m = ((HomogeneousTransformSpecific(0, th1_2)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_3)).inverse())*((HomogeneousTransformSpecific(4, th5_3)).inverse());
    vector<double> p41_3 = {T41m(0,3), T41m(1,3), T41m(2,3)};
    double p41xz_3 = hypot(p41_3[0], p41_3[2]);

    T41m = ((HomogeneousTransformSpecific(0, th1_2)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_4)).inverse())*((HomogeneousTransformSpecific(4, th5_4)).inverse());
    vector<double> p41_4 = {T41m(0,3), T41m(1,3), T41m(2,3)};
    double p41xz_4 = hypot(p41_4[0], p41_4[2]);

//Computation of the 8 possible values for th3
    double th3_1 = adjust_acos((pow(p41xz_1,2)-pow(A[1],2)-pow(A[2], 2))/(2*A[1]*A[2]));
    double th3_2 = adjust_acos((pow(p41xz_2,2)-pow(A[1],2)-pow(A[2],2))/(2*A[1]*A[2]));
    double th3_3 = adjust_acos((pow(p41xz_3,2)-pow(A[1],2)-pow(A[2],2))/(2*A[1]*A[2]));
    double th3_4 = adjust_acos((pow(p41xz_4,2)-pow(A[1],2)-pow(A[2],2))/(2*A[1]*A[2]));

    double th3_5 = adjust_value(-th3_1);
    double th3_6 = adjust_value(-th3_2);
    double th3_7 = adjust_value(-th3_3);
    double th3_8 = adjust_value(-th3_4);

//Computation of eight possible value for th2
    double th2_1=real(atan2(-p41_1[2], -p41_1[0])-adjust_asin((-A[2]*sin(th3_1))/p41xz_1));
    double th2_2=real(atan2(-p41_2[2], -p41_2[0])-adjust_asin((-A[2]*sin(th3_2))/p41xz_2));
    double th2_3=real(atan2(-p41_3[2], -p41_3[0])-adjust_asin((-A[2]*sin(th3_3))/p41xz_3));
    double th2_4=real(atan2(-p41_4[2], -p41_4[0])-adjust_asin((-A[2]*sin(th3_4))/p41xz_4));
    double th2_5=real(atan2(-p41_1[2], -p41_1[0])-adjust_asin((A[2]*sin(th3_1))/p41xz_1));
    double th2_6=real(atan2(-p41_2[2], -p41_2[0])-adjust_asin((A[2]*sin(th3_2))/p41xz_2));
    double th2_7=real(atan2(-p41_3[2], -p41_3[0])-adjust_asin((A[2]*sin(th3_3))/p41xz_3));
    double th2_8=real(atan2(-p41_4[2], -p41_4[0])-adjust_asin((A[2]*sin(th3_4))/p41xz_4));
    
    Matrix44 T43m = ((HomogeneousTransformSpecific(2, th3_1)).inverse())*((HomogeneousTransformSpecific(1, th2_1)).inverse())*((HomogeneousTransformSpecific(0, th1_1)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_1)).inverse())*((HomogeneousTransformSpecific(4, th5_1)).inverse());
        vector<double> Xhat43 = {T43m(0,0), T43m(1,0), T43m(2,0)};
        double th4_1 = real(atan2(Xhat43[1], Xhat43[0]));
    T43m = ((HomogeneousTransformSpecific(2, th3_2)).inverse())*((HomogeneousTransformSpecific(1, th2_2)).inverse())*((HomogeneousTransformSpecific(0, th1_1)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_2)).inverse())*((HomogeneousTransformSpecific(4, th5_2)).inverse());
        Xhat43 = {T43m(0,0), T43m(1,0), T43m(2,0)};
        double th4_2 = real(atan2(Xhat43[1], Xhat43[0]));


        T43m = ((HomogeneousTransformSpecific(2, th3_3)).inverse())*((HomogeneousTransformSpecific(1, th2_3)).inverse())*((HomogeneousTransformSpecific(0, th1_2)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_3)).inverse())*((HomogeneousTransformSpecific(4, th5_3)).inverse());
        Xhat43 = {T43m(0,0), T43m(1,0), T43m(2,0)};
        double th4_3 = real(atan2(Xhat43[1], Xhat43[0]));

        T43m = ((HomogeneousTransformSpecific(2, th3_4)).inverse())*((HomogeneousTransformSpecific(1, th2_4)).inverse())*((HomogeneousTransformSpecific(0, th1_2)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_4)).inverse())*((HomogeneousTransformSpecific(4, th5_4)).inverse());
        Xhat43 = {T43m(0,0), T43m(1,0), T43m(2,0)};
        double th4_4 = real(atan2(Xhat43[1], Xhat43[0]));

        T43m = ((HomogeneousTransformSpecific(2, th3_5)).inverse())*((HomogeneousTransformSpecific(1, th2_5)).inverse())*((HomogeneousTransformSpecific(0, th1_1)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_1)).inverse())*((HomogeneousTransformSpecific(4, th5_1)).inverse());
        Xhat43 = {T43m(0,0), T43m(1,0), T43m(2,0)};
        double th4_5 = real(atan2(Xhat43[1], Xhat43[0]));

        T43m = ((HomogeneousTransformSpecific(2, th3_6)).inverse())*((HomogeneousTransformSpecific(1, th2_6)).inverse())*((HomogeneousTransformSpecific(0, th1_1)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_2)).inverse())*((HomogeneousTransformSpecific(4, th5_2)).inverse());
        Xhat43 = {T43m(0,0), T43m(1,0), T43m(2,0)};
        double th4_6 = real(atan2(Xhat43[1], Xhat43[0]));

        T43m = ((HomogeneousTransformSpecific(2, th3_7)).inverse())*((HomogeneousTransformSpecific(1, th2_7)).inverse())*((HomogeneousTransformSpecific(0, th1_2)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_3)).inverse())*((HomogeneousTransformSpecific(4, th5_3)).inverse());
        Xhat43 = {T43m(0,0), T43m(1,0), T43m(2,0)};
        double th4_7 = real(atan2(Xhat43[1], Xhat43[0]));

        T43m = ((HomogeneousTransformSpecific(2, th3_8)).inverse())*((HomogeneousTransformSpecific(1, th2_8)).inverse())*((HomogeneousTransformSpecific(0, th1_2)).inverse())*T60*((HomogeneousTransformSpecific(5, th6_4)).inverse())*((HomogeneousTransformSpecific(4, th5_4)).inverse());
        Xhat43 = {T43m(0,0), T43m(1,0), T43m(2,0)};
        double th4_8 = real(atan2(Xhat43[1], Xhat43[0]));
    Matrix86 Th;
    Th << th1_1, th2_1, th3_1, th4_1, th5_1, th6_1,
          th1_1, th2_2, th3_2, th4_2, th5_2, th6_2,
          th1_2, th2_3, th3_3, th4_3, th5_3, th6_3,
          th1_2, th2_4, th3_4, th4_4, th5_4, th6_4,
          th1_1, th2_5, th3_5, th4_5, th5_1, th6_1,
          th1_1, th2_6, th3_6, th4_6, th5_2, th6_2,
          th1_2, th2_7, th3_7, th4_7, th5_3, th6_3,
          th1_2, th2_8, th3_8, th4_8, th5_4, th6_4;
    cout << Th << endl;
    return Th;
}
bool checkPosition (Vector3d pos, Matrix16 q) {
    Matrix3d m;
    m << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;
    MatrixD6 qf=Ur5Inverse(pos, m);
    if (!bestInverse(q, qf)) {
        return false;
    }
    Matrix16 Th=qf.row(0);
    pair<Vector3d, Matrix3d> endEffector=Ur5Direct(Th);
    endEffector.first(1)=-endEffector.first(1);
    endEffector.first(2)=-endEffector.first(2);
    for (int i=0; i<3; i++) {
        if(pow(endEffector.first(i)-pos(i), 2)>ERROR*ERROR) {
            return false;
        }
    }
    return true;
}
