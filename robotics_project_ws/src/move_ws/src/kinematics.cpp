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
const double JOINT_MIN[] = {-2*M_PI, -M_PI, -M_PI, -2*M_PI, -2*M_PI, -2*M_PI};
const double JOINT_MAX[] = { 2*M_PI,  0,  M_PI,  2*M_PI,  2*M_PI_2,  2*M_PI};

/***************************************
*
* adjust_value() - Adjusts a float value
* to zero if it is close to zero.
*
* Input:
* - x (float): The input value to be checked.
*
* Output:
* - (float): Returns 0 if the input value
*   is within the range (-1e-6, 1e-6).
*   Otherwise, returns the original value.
*
***************************************/
float adjust_value(float x) {
    if(x<1e-6 && x>-1e-6) {
        return 0;
    }
    return x;
}

/***************************************
*
* adjust_asin() - Adjusts the value to ensure
* it's within the valid domain of the
* asin() function.
*
* Input:
* - x (float): The input value to be adjusted.
*
* Output:
* - (float): Returns -π/2 if the input is less
*   than -1, π/2 if the input is greater than 1,
*   and asin(x) otherwise.
*
***************************************/
float adjust_asin(float x) {
    if(x<-1) {
        return -M_PI/2;
    }
    if(x>1) {
        return M_PI/2;
    }
    return asin(x);
}

/***************************************
*
* adjust_acos() - Adjusts a value to ensure
* it is within the valid domain of the
* acos() function.
*
* Input:
* - x (float): The input value to be adjusted.
*
* Output:
* - (float): Returns π if the input is less
*   than -1, 0 if the input is greater than 1,
*   and acos(x) otherwise.
*
***************************************/
float adjust_acos(float x) {
    if(x<-1) {
        return M_PI;
    }
    if(x>1) {
        return 0;
    }
    return acos(x);
}

/***************************************
*
* eul2rotm() - Converts Euler angles to
* a 3D rotation matrix, applying the 
* rotations in the order:
* z-axis, then y-axis, and x-axis.
*
* Input:
* - phiEf (Vector3d): A vector containing the
*   Euler angles (in radians) in the order:
*   [yaw (z-axis), pitch (y-axis), roll (x-axis)].
*
* Output:
* - (Matrix3d): A 3x3 rotation matrix
*   representing the combined rotations
*   around the z, y, and x axes.
*
***************************************/
Matrix3d eul2rotm(Vector3d phiEf) {
    return zRot(phiEf(0)) * yRot(phiEf(1)) * xRot(phiEf(2));
}

/***************************************
*
* rotm2eul() - Converts a 3D rotation matrix
* to Euler angles. Handles singularities.
*
* Input:
* - m (Matrix3d): A 3x3 rotation matrix representing
*   a 3D rotation.
*
* Output:
* - (Vector3d): A vector containing the Euler angles
*   (in radians) in the order:
*   [yaw (z-axis), pitch (y-axis), roll (x-axis)].
*
***************************************/
// Source of the pseudocode: https://www.geometrictools.com/Documentation/EulerAngles.pdf Z-Y-X
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

/***************************************
*
* removeRow() - Removes a specified row
* from a dynamic matrix and shifts all rows 
* below up by one position. Then resizes the matrix.
*
* Input:
* - m (MatrixD6*): A pointer to the matrix
*   from which a row will be removed.
* - remove (unsigned int): The index of the
*   row to be removed (0-based).
*
* No output
*
***************************************/
void removeRow(MatrixD6* m, unsigned int remove) {
    unsigned long int numRows = m->rows()-1;
    unsigned long int numCols = m->cols();
    if( remove < numRows ) {
        m->block(remove,0,numRows-remove,numCols) = m->block(remove+1,0,numRows-remove,numCols);
    }
    m->conservativeResize(numRows,numCols);
}

/***************************************
*
* bestInverse() - Filters and sorts inverse
* kinematics solutions to select the best
* configuration.
*
* Input:
* - start (Matrix16): A matrix representing
*   the starting configuration of the system.
* - end (MatrixD6&): A reference to a matrix
*   containing potential solutions (rows of
*   joint angles).
*
* Output:
* - (bool): Returns `true` if at least one valid
*   solution remains after filtering; otherwise,
*   returns `false`.
*
***************************************/
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
    /*while (i<end.rows()){
        Matrix16 thi=end.row(i);
        if (!checkAngles(&thi)){
            removeRow(&end, i);
            cout << "Row " << i << " REMOVED" << endl;
        } else {
            i++;
        }
    }*/
    std::vector<double> configs(end.rows());
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
   /* if (end.size()==0) {
        cout << "NO POSSIBLE ERROR TRAJECTORY" << endl;
        return false;
    }*/
    return true;
}

double hypot(double x1, double x2){
    double hy = sqrt(x1*x1 + x2*x2);
    return hy;
}

void computeJointPositions(Matrix61 th, Vector3d jointPositions[NUM_JOINTS]) {
    MatrixD4 matrices[NUM_JOINTS];
    for (int i=0; i<NUM_JOINTS; i++) {
        matrices[i]=HomogeneousTransformSpecific(i, th[i]);
        //cout << "Transformation Matrix for Joint " << i + 1 << ":" << endl;
        //cout << matrices[i] << endl;
    }
    Matrix4d Id;
    Id << 1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1;
    //Vector3d v;
    for (int i=0; i<NUM_JOINTS; i++) {
        Id=Id*matrices[i];
        for (int j=0; j<4; j++) {
            for (int k=0; k<4; k++) {
                Id(j, k)=adjust_value(Id(j, k));
            }
        }
        //cout << "Transformation From " << i << "to " << i+1 << ":" << endl;
        //cout << Id << endl;
        //v << Id(0, 3), Id(1, 3), Id(2, 3);
        //jointPositions.push_back(v);
        jointPositions[i] << Id(0, 3), Id(1, 3), Id(2, 3);
        //cout << i+1 << " " << jointPositions[i](0) << " " << jointPositions[i](1) << " " << jointPositions[i](2) << endl;
    }
}
bool checkAngles(Matrix16* th) {
    bool ret=true;
    for (int i=0; i<NUM_JOINTS && ret; i++) {
        if(!((*th)(i)-JOINT_MIN[i]>0.001 && 0.001<-(*th)(i)+JOINT_MAX[i])) {
            cout << "ERROR ANGLES " << (*th)(i) << "   " << i+1 << " " << JOINT_MIN[i] << "-" << JOINT_MAX[i] << endl;
            ret=false;
        }
    }
    //Check collision
    if(ret) {
        if(!control_collision(th)) {
            ret=false;
        }
    }
    return ret;
}

bool control_collision(Matrix16* th) {
    MatrixD4 matrices[NUM_JOINTS];
    for (int i=0; i<NUM_JOINTS; i++) {
        matrices[i]=HomogeneousTransformSpecific(i, (*th)(i));
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
        //Input doesn't change
        if(pos_x<XMIN || pos_x>XMAX) {
            cout << "COLLISION X: " << pos_x << " " << XMIN << " " << XMAX << " " << i+1 << endl;
            return false;
        }
        //Input negates, so above -0.2
        if(pos_y<YMIN || pos_y>YMAX(i)) {
            cout << "COLLISION Y: " << pos_y << " " << YMIN << " " << YMAX(i) << " " << i+1 << endl;
            return false;
        }
        //Input negates, so from -0.9 - 0
        if(pos_z < ZMIN || pos_z>ZMAX(i)) {
            cout << "COLLISION Z: " << pos_z << " " << ZMIN << " " << ZMAX(i) << " " << i+1 << endl;
            return false;
        }
    }
    return true;
    
}

VectorXd cubicPolynomial(double P_start, double P_end, int minT, int maxT) {
    Matrix44 M;
    M << 1, minT, pow(minT, 2), pow(minT, 3),
         0, 1, 2 * minT, 3 * pow(minT, 2),
         1, maxT, pow(maxT, 2), pow(maxT, 3),
         0, 1, 2 * maxT, 3 * pow(maxT, 2);
    
    VectorXd b(4);
    b << P_start, 0, P_end, 0;  // Zero velocity at start & end

    return M.colPivHouseholderQr().solve(b);
}

bool checkJointLimits(const Matrix61 q) {
    for (int i = 0; i < NUM_JOINTS; ++i) {
        if (q(i) < JOINT_MIN[i] || q(i) > JOINT_MAX[i]) {
            std::cout << "Joint " << i+1 << " out of bounds! q(" << i << ") = " << q(i) << endl;
            return false;
        }
    }
    return true;
}

double evaluateCubic(const VectorXd& coeffs, double t) {
    return coeffs(0) + coeffs(1) * t + coeffs(2) * pow(t, 2) + coeffs(3) * pow(t, 3);
}

Vector3d smoothBlend(Vector3d old_xE, Vector3d new_xE, double alpha) {
    return old_xE * (1 - alpha) + new_xE * alpha;  // Weighted average
}

bool checkJointOperationalSpace(const Vector3d jointPositions[NUM_JOINTS], int& val) {
    for (size_t i = 1; i < NUM_JOINTS; ++i) {
        const Vector3d pos = jointPositions[i];  // Use reference to avoid copy
        //cout << "CHECKING WORKSPACE " << i << ": "<< pos(0) << " " << pos(1) << " " << pos(2);
        if (pos(0) < XMIN || pos(0) > XMAX ||
            pos(1) < YMIN || pos(1) > YMAX(i) ||  // Ensure YMAX(i) is defined
            pos(2) < ZMIN || pos(2) > ZMAX(i)) {
            cout << "Joint " << i+1 << " is out of workspace! Position: "
                      << pos(0) << " " << pos(1) << " " << pos(2);
            val=i;
            return false;
        }
    }
    return true;
}

void adjustTrajectory(Matrix61& q) {
    const double adjustmentStep = 0.01;  // Step size for joint adjustment
    for(int i=0; i<NUM_JOINTS-1; i++) {
        q(i)=singularityCheck(i+1, q(i));
    }
    Vector3d jointPositions[NUM_JOINTS];
    computeJointPositions(q, jointPositions);
    // Use all joint positions
    int val=0;
    while (!checkJointOperationalSpace(jointPositions, val)) {
            //cout << "Adjusting Joint " << val+1 << endl;
            //cout << "Before Adjustment - Joint Angle: " << q(val) << endl;
            if (q(val)>JOINT_MIN[val]) {
                q(val) += adjustmentStep;  // Move joint to a safer position
            }
            else {
                if(q(val)<JOINT_MAX[val]) {
                    q(val)-=adjustmentStep;
                }
            }
        
            // Normalize the joint angle to the range [-π, π]
            if (q(val) > M_PI) {
                q(val) -= 2 * M_PI;
            } else if (q(val) < -M_PI) {
                q(val) += 2 * M_PI;
            }
            
            q(val)=singularityCheck(val+1, q(val));
            cout << ". q(" << val+1 << ")=" << q(val) << endl;
            //cout << "After Adjustment - Joint Angle: " << q(val) << endl;
            // Recompute joint positions after adjustment
            computeJointPositions(q, jointPositions);
            //cout << "Joint " << val + 1 << " Position After Adjustment: " << jointPositions[val].transpose() << endl;
    }
}

void clampJointAngles(Matrix61& q) {
    for (int i = 0; i < NUM_JOINTS; ++i) {
        if (q(i) < JOINT_MIN[i]) q(i) = JOINT_MIN[i]+ERROR;
        if (q(i) > JOINT_MAX[i]) q(i) = JOINT_MAX[i]-ERROR;
    }
}

Matrix66 computeJacobian(const Matrix61& q) {
    Matrix66 J;
    J.setZero();

    // Compute the forward kinematics for each joint
    vector<Matrix44> T(NUM_JOINTS);
    Matrix44 T_total;
    T_total << 1, 0, 0, 0,
               0, 1, 0, 0,
               0, 0, 1, 0,
               0, 0, 0, 1;
    
    for (int i = 0; i < NUM_JOINTS; i++) {
        T[i] = HomogeneousTransformSpecific(i, q(i));
        T_total = T_total * T[i];
    }

    // Compute the position of each joint
    vector<Vector3d> joint_positions(NUM_JOINTS);
    Matrix4d T_current = Matrix4d::Identity();
    for (int i = 0; i < NUM_JOINTS; i++) {
        T_current = Matrix4d::Identity();  // Reset transformation
        for (int j = 0; j <= i; j++) {
            T_current *= T[j];  // Compute up to joint i
        }

        Vector3d z_axis = T_current.block<3, 1>(0, 2);  // Z-axis of the joint
        Vector3d position_diff = joint_positions.back() - joint_positions[i];

        J.block<3, 1>(0, i) = z_axis.cross(position_diff);  // Linear velocity component
        J.block<3, 1>(3, i) = z_axis;  // Angular velocity component
    }
    /*for (int i = 0; i < NUM_JOINTS; i++) {
        T_current = T_current * T[i];
        joint_positions[i] = T_current.block<3, 1>(0, 3);
    }

    // Compute the Jacobian columns
    for (int i = 0; i < NUM_JOINTS; i++) {
        Vector3d z_axis = T[i].block<3, 1>(0, 2);
        Vector3d position_diff = joint_positions.back() - joint_positions[i];  // Position difference
        J.block<3, 1>(0, i) = z_axis.cross(position_diff);  // Linear velocity component
        J.block<3, 1>(3, i) = z_axis;  // Angular velocity component
    }*/

    return J;
}

Matrix61 computeJointAdjustment(Vector3d pos_error, Vector3d ori_error, Matrix61 current) {
    double lambda=0.01;
    double adjustmentStep=0.1;
    Matrix66 J=computeJacobian(current);
    Matrix61 cartesian_error;
    cartesian_error << pos_error, ori_error;
    Matrix66 Id;
    Id << 1, 0, 0, 0, 0, 0,
          0, 1, 0, 0, 0, 0,
          0, 0, 1, 0, 0, 0,
          0, 0, 0, 1, 0, 0,
          0, 0, 0, 0, 1, 0,
          0, 0, 0, 0, 0, 1;
    Matrix66 J_pseudo_inverse =(J.transpose()*J+lambda* Id).ldlt().solve(J.transpose()); //J.completeOrthogonalDecomposition().pseudoInverse();
    Matrix61 cartesian_velocity;
    cartesian_velocity << 0, 0, 0.1, 0, 0, 0;
    //Matrix61 q_adjustment = J_pseudo_inverse * cartesian_error;
    Matrix61 q_dot = J_pseudo_inverse * cartesian_velocity;
    Matrix61 q;
    q = q+ DELTAT * q_dot;
    return q;
}

bool linear_interpolation(Matrix61 qEs, Vector3d xES, Vector3d xEF, Vector3d phiEf, int minT, int maxT, MatrixD6* Th) {
    MatrixD6 q_end;
    cout << "XES: " << xES << endl;
    cout << "XEF: " << xEF << endl;
    double position_tolerance = 0.05;
    double orientation_tolerance = 0.05;
    // Compute Inverse Kinematics
    q_end=Ur5Inverse(xEF, eul2rotm(phiEf));
    
    // Select the best IK solution
    if (!bestInverse(qEs, q_end)) {
        cout << "No valid smooth inverse kinematics solution found!" << endl;
        return false;
    }
    int choose_inv=0;
    Matrix61 qEf;
    bool reached=false;
    for (int i=0; i<q_end.rows() && !reached; i++) {
        qEf= q_end.row(choose_inv);
        cout << qEf << endl;
        if (!checkJointLimits(qEf)) {
            clampJointAngles(qEf);
        }
        int maxIterations = 1000;
        int iteration = 0;
        
        while (!reached && iteration++ < maxIterations) {
            pair<Vector3d, Matrix3d> actual = Ur5Direct(qEf);
            Vector3d pos_error = xEF - actual.first;
            cout << "POS: " << pos_error << " " << xEF << " " << actual.first;
            Vector3d ori_error=rotm2eul(eul2rotm(phiEf)*actual.second.transpose());
            cout << "ORI: " << ori_error << " " << eul2rotm(phiEf) << " " << actual.second.transpose();
            if(pos_error.norm()<position_tolerance && ori_error.norm()<orientation_tolerance) {
                reached=true;
            }
            else {
                Matrix61 adjustment=computeJointAdjustment(pos_error, ori_error, qEf);
                qEf=qEf+adjustment;
            }
        }
        if(!reached) {
            choose_inv++;
            if (choose_inv >= q_end.rows()) {
               cout << "Warning: No valid inverse kinematics solution found!" << endl;
               return false;
           }
        }
    }
    // Store polynomial coefficients for each joint
    VectorXd coeffs[NUM_JOINTS];
    
    for (int i = 0; i < NUM_JOINTS; ++i) {
        coeffs[i] = cubicPolynomial(qEs(i), qEf(i), minT, maxT);
    }
    
    int numSteps = static_cast<int>((maxT - minT) / DELTAT) + 1;
    int step=0;
    // Generate smooth trajectory
    for (double t = minT; t <= maxT; t += DELTAT) {
        Matrix61 q_t;
        for (int i = 0; i < NUM_JOINTS; ++i) {
            q_t(i) = evaluateCubic(coeffs[i], t);
        }
        if (!checkJointLimits(q_t)) {
            clampJointAngles(q_t);
        }
        adjustTrajectory(q_t);  // Adjust trajectory if joint is out of workspace
        /*auto [xE, rot] = Ur5Direct(q_t);
        Vector3d adjusted_xE = adjustTrajectory(xE);
        if (!(adjusted_xE(0)==xE(0) && adjusted_xE(1)==xE(1) && adjusted_xE(2)==xE(2))) {
            MatrixD6 q_candidates = Ur5Inverse(smoothBlend(xE, adjusted_xE, 0.2), rot);
            if (q_candidates.rows() == 0) {
                cout << "Skipping step: No valid IK solutions." << endl;
                continue;
            }
            if (!bestInverse(qEs, q_candidates)) {
                cout << "No valid smooth inverse kinematics solution found!" << endl;
                return false;
            }
            q_t = q_candidates.row(0);
        }*/
       
        // Append the trajectory
        //Th->row(step++) = q_t;
        Th->conservativeResize(Th->rows() + 1, NUM_JOINTS);
        Th->row(Th->rows() - 1) = q_t;

        cout << "Time: " << t << " --> Joint Angles: " << q_t.transpose() << endl;
    }

    return true;
}

bool p2pMotionPlanPerturbation(Matrix61 qES, Vector3d xEf, Vector3d phiEf, int minT, int maxT, MatrixD6* Th, bool velocity, InverseType inv, double rot_gripper) {
    MatrixXd xE;
    MatrixXd phiE;
    MatrixD6 qEF;
    cout << "XEF: " << xEf << endl;

    // Compute start position in Cartesian space
    auto [xE_start, _] = Ur5Direct(qES);
    cout << "xE_start: " << xE_start << endl;

    // Compute inverse kinematics for the desired end-effector position and orientation
   qEF = Ur5Inverse(xEf, eul2rotm(phiEf));

    if (!bestInverse(qES, qEF)) {
        cout << "No Inverse is admissible" << endl;
        return false;
    }

    cout << "qEF: " << qEF << endl;
    double dt = DELTAT;
    if (!velocity) {
        dt = dt / 2;
    }

    // Generate trajectory with polynomial interpolation between qES and qEF
    for (int i = 0; i < qEF.rows(); ++i) {
        MatrixD6 A;
        bool error = false;
        MatrixD6 tempTh;

        for (int j = 0; j < qES.rows(); j++) {
            MatrixXd M(6, 6);
            M << 1, minT, pow(minT, 2), pow(minT, 3), pow(minT, 4), pow(minT, 5),
                 0, 1, 2 * minT, 3 * pow(minT, 2), 4 * pow(minT, 3), 5 * pow(minT, 4),
                 0, 0, 2, 6 * minT, 12 * pow(minT, 2), 20 * pow(minT, 3),
                 1, maxT, pow(maxT, 2), pow(maxT, 3), pow(maxT, 4), pow(maxT, 5),
                 0, 1, 2 * maxT, 3 * pow(maxT, 2), 4 * pow(maxT, 3), 5 * pow(maxT, 4),
                 0, 0, 2, 6 * maxT, 12 * pow(maxT, 2), 20 * pow(maxT, 3);

            VectorXd b(6);
            b << qES(j), 0, 0, qEF(i, j), 0, 0;

            MatrixXd M_inv = M.inverse();
            VectorXd coeff = M_inv * b;
            A.conservativeResize(A.rows() + 1, Eigen::NoChange);
            A.row(A.rows() - 1) = coeff.transpose();
        }

        for (double t = minT; t < maxT + dt && !error; t += dt) {
            Matrix16 th;
            for (int k = 0; k < qES.rows(); k++) {
                th(k) = A(k, 0) + A(k, 1) * t + A(k, 2) * pow(t, 2) + A(k, 3) * pow(t, 3) + A(k, 4) * pow(t, 4) + A(k, 5) * pow(t, 5);
            }

            cout << "Time " << t << ": " << th.transpose() << endl;
            if (!checkAngles(&th) || !control_collision(&th)) {
                cout << "Trajectory Error at t=" << t << " - Attempting correction..." << endl;
                bool corrected = false;
                for (int joint = 0; joint < NUM_JOINTS; joint++) {
                    double original_value = th(joint);

                    // Try perturbing the joint in small increments
                    for (double perturb = 0; perturb < 2 * M_PI && !corrected; perturb += DELTAT) {
                        th(joint) = original_value + perturb;

                        // Recheck after perturbing just one joint
                        if (!checkAngles(&th) || !control_collision(&th)) {
                            cout << "Perturbation failed for joint " << joint << " at t=" << t << ", trying next perturbation..." << endl;
                        } else {
                            cout << "Correction successful for joint " << joint << " at t=" << t << endl;
                            corrected = true;
                            break;
                        }
                    }

                    if (corrected) {
                        break;
                    }
                }
                if (!corrected) {
                    cout << "No valid correction found for t=" << t << " - Trajectory Error remains." << endl;
                    error = true;
                }
            }

            tempTh.conservativeResize(tempTh.rows() + 1, NUM_JOINTS);
            tempTh.row(tempTh.rows() - 1) = th;
        }

        if (!error) {
            Th->conservativeResize(Th->rows() + tempTh.rows(), NUM_JOINTS);
            Th->bottomRows(tempTh.rows()) = tempTh;
            return true;
        }
    }

    return false;  // Return false if no valid trajectory was found
}

bool p2pMotionPlan(Matrix61 qES, Vector3d xEf, Vector3d phiEf, int minT, int maxT, MatrixD6* Th, bool velocity, InverseType inv, double rot_gripper) {
    MatrixXd xE;
    MatrixXd phiE;
    MatrixD6 qEF;
    cout << "XEF: " << xEf << endl;

    // Compute start position in Cartesian space
    auto [xE_start, _] = Ur5Direct(qES);
    cout << "xE_start: " << xE_start << endl;

    // Compute inverse kinematics for the desired end-effector position and orientation
   qEF = Ur5Inverse(xEf, eul2rotm(phiEf));

    if (!bestInverse(qES, qEF)) {
        cout << "No Inverse is admissible" << endl;
        return false;
    }

    cout << "qEF: " << qEF << endl;
    double dt = DELTAT;
    if (!velocity) {
        dt = dt / 2;
    }

    // Generate trajectory with polynomial interpolation between qES and qEF
    for (int i = 0; i < qEF.rows(); ++i) {
        MatrixD6 A;
        bool error = false;
        MatrixD6 tempTh;

        for (int j = 0; j < qES.rows(); j++) {
            MatrixXd M(6, 6);
            M << 1, minT, pow(minT, 2), pow(minT, 3), pow(minT, 4), pow(minT, 5),
                 0, 1, 2 * minT, 3 * pow(minT, 2), 4 * pow(minT, 3), 5 * pow(minT, 4),
                 0, 0, 2, 6 * minT, 12 * pow(minT, 2), 20 * pow(minT, 3),
                 1, maxT, pow(maxT, 2), pow(maxT, 3), pow(maxT, 4), pow(maxT, 5),
                 0, 1, 2 * maxT, 3 * pow(maxT, 2), 4 * pow(maxT, 3), 5 * pow(maxT, 4),
                 0, 0, 2, 6 * maxT, 12 * pow(maxT, 2), 20 * pow(maxT, 3);

            VectorXd b(6);
            b << qES(j), 0, 0, qEF(i, j), 0, 0;

            MatrixXd M_inv = M.inverse();
            VectorXd coeff = M_inv * b;
            A.conservativeResize(A.rows() + 1, Eigen::NoChange);
            A.row(A.rows() - 1) = coeff.transpose();
        }

        for (double t = minT; t < maxT + dt && !error; t += dt) {
            Matrix16 th;
            for (int k = 0; k < qES.rows(); k++) {
                th(k) = A(k, 0) + A(k, 1) * t + A(k, 2) * pow(t, 2) + A(k, 3) * pow(t, 3) + A(k, 4) * pow(t, 4) + A(k, 5) * pow(t, 5);
            }
            if(!checkAngles(&th)) {
                cout << "TRAJECTORY ERROR" << endl;
                error =true;
            }
            tempTh.conservativeResize(tempTh.rows() + 1, NUM_JOINTS);
            tempTh.row(tempTh.rows() - 1) = th;
        }

        if (!error) {
            Th->conservativeResize(Th->rows() + tempTh.rows(), NUM_JOINTS);
            Th->bottomRows(tempTh.rows()) = tempTh;
            return true;
        }
    }

    return false;  // Return false if no valid trajectory was found
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
        T=HomogeneousTransformSpecific(i, Th[i]);
        T60=T60*T;
    }
    Vector3d v;
    Matrix3d m;
    v << T60(0, 3), T60(1, 3), T60 (2, 3);
    m << T60(0, 0), T60(0, 1), T60(0, 2),
         T60(1, 0), T60(1, 1), T60(1, 2),
         T60(2, 0), T60(2, 1), T60(2, 2);
    return make_pair(v, m);
}

double singularityCheck(int angle, double value) {
    if(angle==3) {
        if(abs(value)<1e-6) {
            value=1e-6;
            cout << "Warning: angle " << angle << " near singularity, adjusted to avoid instability." << endl;
        }
    }
    else {
        if(angle==5) {
            if (abs(value) < 1e-6 || abs(value - M_PI) < 1e-6) {
                cout << "Warning: angle " << angle << " near singularity detected,  adjusted to avoid instability." << endl;
                value = value > 0 ? 1e-6 : -1e-6;
            }
        }
        else {
            if(angle==2) {
                if (abs(abs(angle) - M_PI_2) < 1e-6) {
                    cout << "Warning: angle " << angle << " near singularity detected,  adjusted to avoid instability." << endl;
                    value = value+(value > 0 ? -1e-6 : 1e-6);
                }
            }
        }
    }
    return value;
}
//VERTICAL MOTION TH1 TH5 TH6 FIXED
//HORIZONTAL MOTION
Matrix86 Ur5Inverse(Vector3d v, Matrix3d m){ //vector = punti di destinazione; m= matrice rotazionale
    Matrix44 T60;
    //v[1]=-v[1];
    //v[2]=-v[2];
    T60 << m(0,0), m(0,1), m(0,2), v(0),
           m(1,0), m(1,1), m(1,2), v(1),
           m(2,0), m(2,1), m(2,2), v(2),
           0,0,0,1;
//th1
    
    Matrix41 tmp;
    tmp << 0,0,-D[5],1;
    Matrix14 p50=T60*tmp;
    double th1_1 = real((atan2(p50(1), p50(0)) + adjust_acos(D[3]/hypot(p50(1), p50(0))))+ M_PI_2);
    double th1_2 = real((atan2(p50(1), p50(0)) - adjust_acos(D[3]/hypot(p50(1), p50(0))))+ M_PI_2);
//th5
    double th5_1 =adjust_acos((v(0)*sin(th1_1) - v(1)*cos(th1_1)-D[3]) / D[5]);
    double th5_2 =-adjust_acos((v(0)*sin(th1_1) - v(1)*cos(th1_1)-D[3]) / D[5]);
    double th5_3 =adjust_acos((v(0)*sin(th1_2) - v(1)*cos(th1_2)-D[3]) / D[5]);
    double th5_4 =-adjust_acos((v(0)*sin(th1_2) - v(1)*cos(th1_2)-D[3]) / D[5]);
    
    th5_1=singularityCheck(5, th5_1);
    th5_2=singularityCheck(5, th5_2);
    th5_3=singularityCheck(5, th5_3);
    th5_4=singularityCheck(5, th5_4);
//related to th11 a th51
    Matrix44 T06 = T60.inverse();
    vector<double> Xhat = {T06(0,0), T06(1,0), T06(2,0)};
    vector<double> Yhat = {T06(0,1), T06(1,1), T06(2,1)};
    double th6_1 =real(atan2(((-Xhat[1]*sin(th1_1)+Yhat[1]*cos(th1_1)))/sin(th5_1), ((Xhat[0]*sin(th1_1)-Yhat[0]*cos(th1_1)))/sin(th5_1)));
//related to th11 a th52
    double th6_2 =real(atan2(((-Xhat[1]*sin(th1_1)+Yhat[1]*cos(th1_1))/sin(th5_2)), ((Xhat[0]*sin(th1_1)-Yhat[0]*cos(th1_1))/sin(th5_2))));
//related to th12 a th53
    double th6_3 =real(atan2(((-Xhat[1]*sin(th1_2)+Yhat[1]*cos(th1_2))/sin(th5_3)), ((Xhat[0]*sin(th1_2)-Yhat[0]*cos(th1_2))/sin(th5_3))));
//related to th12 a th54
    double th6_4 =real(atan2(((-Xhat[1]*sin(th1_2)+Yhat[1]*cos(th1_2))/sin(th5_4)), ((Xhat[0]*sin(th1_2)-Yhat[0]*cos(th1_2))/sin(th5_4))));


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
    double th3_1=adjust_acos(pow(p41xz_1,2)-pow(A[1],2)-pow(A[2], 2)/(2*A[1]*A[2]));
    double th3_2=adjust_acos(pow(p41xz_2,2)-pow(A[1],2)-pow(A[2], 2)/(2*A[1]*A[2]));
    
    double th3_3=adjust_acos(pow(p41xz_3,2)-pow(A[1],2)-pow(A[2], 2)/(2*A[1]*A[2]));
    double th3_4=adjust_acos(pow(p41xz_4,2)-pow(A[1],2)-pow(A[2], 2)/(2*A[1]*A[2]));
    double th3_5 = adjust_value(-th3_1);
    double th3_6 = adjust_value(-th3_2);
    double th3_7 = adjust_value(-th3_3);
    double th3_8 = adjust_value(-th3_4);
    th3_1=singularityCheck(3, th3_1);
    th3_2=singularityCheck(3, th3_2);
    th3_3=singularityCheck(3, th3_3);
    th3_4=singularityCheck(3, th3_4);
    th3_5=singularityCheck(3, th3_5);
    th3_6=singularityCheck(3, th3_6);
    th3_7=singularityCheck(3, th3_7);
    th3_8=singularityCheck(3, th3_8);
//Computation of eight possible value for th2
    double th2_1=real(atan2(-p41_1[2], -p41_1[0])-adjust_asin((-A[2]*sin(th3_1))/p41xz_1));
    double th2_2=real(atan2(-p41_2[2], -p41_2[0])-adjust_asin((-A[2]*sin(th3_2))/p41xz_2));
    double th2_3=real(atan2(-p41_3[2], -p41_3[0])-adjust_asin((-A[2]*sin(th3_3))/p41xz_3));
    double th2_4=real(atan2(-p41_4[2], -p41_4[0])-adjust_asin((-A[2]*sin(th3_4))/p41xz_4));
    double th2_5=real(atan2(-p41_1[2], -p41_1[0])-adjust_asin((A[2]*sin(th3_1))/p41xz_1));
    double th2_6=real(atan2(-p41_2[2], -p41_2[0])-adjust_asin((A[2]*sin(th3_2))/p41xz_2));
    double th2_7=real(atan2(-p41_3[2], -p41_3[0])-adjust_asin((A[2]*sin(th3_3))/p41xz_3));
    double th2_8=real(atan2(-p41_4[2], -p41_4[0])-adjust_asin((A[2]*sin(th3_4))/p41xz_4));
    
    th2_1=singularityCheck(2, th2_1);
    th2_2=singularityCheck(2, th2_2);
    th2_3=singularityCheck(2, th2_3);
    th2_4=singularityCheck(2, th2_4);
    th2_5=singularityCheck(2, th2_5);
    th2_6=singularityCheck(2, th2_6);
    th2_7=singularityCheck(2, th2_7);
    th2_8=singularityCheck(2, th2_8);
    
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
Matrix86 Ur5InverseVerticalZ(Vector3d v, Matrix3d m, double th1, double th5, double th6){ //vector = punti di destinazione; m= matrice rotazionale
    Matrix44 T60;
    //v[1]=-v[1];
    //v[2]=-v[2];
    T60 << m(0,0), m(0,1), m(0,2), v(0),
           m(1,0), m(1,1), m(1,2), v(1),
           m(2,0), m(2,1), m(2,2), v(2),
           0,0,0,1;
//th1
    
    Matrix41 tmp;
    tmp << 0,0,-D[5],1;
    Matrix14 p50=T60*tmp;
    double th1_1=th1;
    double th1_2=th1;
    double th5_1 =th5;
    double th5_2 =th5;
    double th5_3 =th5;
    double th5_4 =th5;
    
    th5_1=singularityCheck(5, th5_1);
    th5_2=singularityCheck(5, th5_2);
    th5_3=singularityCheck(5, th5_3);
    th5_4=singularityCheck(5, th5_4);
//related to th11 a th51
    Matrix44 T06 = T60.inverse();
    vector<double> Xhat = {T06(0,0), T06(1,0), T06(2,0)};
    vector<double> Yhat = {T06(0,1), T06(1,1), T06(2,1)};
    double th6_1 =th6;
//related to th11 a th52
    double th6_2 =th6;
//related to th12 a th53
    double th6_3 =th6;
//related to th12 a th54
    double th6_4 =th6;

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
    double th3_1=adjust_acos(pow(p41xz_1,2)-pow(A[1],2)-pow(A[2], 2)/(2*A[1]*A[2]));
    double th3_2=adjust_acos(pow(p41xz_2,2)-pow(A[1],2)-pow(A[2], 2)/(2*A[1]*A[2]));
    
    double th3_3=adjust_acos(pow(p41xz_3,2)-pow(A[1],2)-pow(A[2], 2)/(2*A[1]*A[2]));
    double th3_4=adjust_acos(pow(p41xz_4,2)-pow(A[1],2)-pow(A[2], 2)/(2*A[1]*A[2]));
    double th3_5 = adjust_value(-th3_1);
    double th3_6 = adjust_value(-th3_2);
    double th3_7 = adjust_value(-th3_3);
    double th3_8 = adjust_value(-th3_4);
    th3_1=singularityCheck(3, th3_1);
    th3_2=singularityCheck(3, th3_2);
    th3_3=singularityCheck(3, th3_3);
    th3_4=singularityCheck(3, th3_4);
    th3_5=singularityCheck(3, th3_5);
    th3_6=singularityCheck(3, th3_6);
    th3_7=singularityCheck(3, th3_7);
    th3_8=singularityCheck(3, th3_8);
//Computation of eight possible value for th2
    double th2_1=real(atan2(-p41_1[2], -p41_1[0])-adjust_asin((-A[2]*sin(th3_1))/p41xz_1));
    double th2_2=real(atan2(-p41_2[2], -p41_2[0])-adjust_asin((-A[2]*sin(th3_2))/p41xz_2));
    double th2_3=real(atan2(-p41_3[2], -p41_3[0])-adjust_asin((-A[2]*sin(th3_3))/p41xz_3));
    double th2_4=real(atan2(-p41_4[2], -p41_4[0])-adjust_asin((-A[2]*sin(th3_4))/p41xz_4));
    double th2_5=real(atan2(-p41_1[2], -p41_1[0])-adjust_asin((A[2]*sin(th3_1))/p41xz_1));
    double th2_6=real(atan2(-p41_2[2], -p41_2[0])-adjust_asin((A[2]*sin(th3_2))/p41xz_2));
    double th2_7=real(atan2(-p41_3[2], -p41_3[0])-adjust_asin((A[2]*sin(th3_3))/p41xz_3));
    double th2_8=real(atan2(-p41_4[2], -p41_4[0])-adjust_asin((A[2]*sin(th3_4))/p41xz_4));
    
    th2_1=singularityCheck(2, th2_1);
    th2_2=singularityCheck(2, th2_2);
    th2_3=singularityCheck(2, th2_3);
    th2_4=singularityCheck(2, th2_4);
    th2_5=singularityCheck(2, th2_5);
    th2_6=singularityCheck(2, th2_6);
    th2_7=singularityCheck(2, th2_7);
    th2_8=singularityCheck(2, th2_8);
    
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

bool cartesianInterpolation (Matrix61 qES, Vector3d xEf, Vector3d phiEf, int minT, int maxT, MatrixD6* Th, bool velocity, InverseType inv, double rot_gripper) {
    double dt = DELTAT;
    int num_points=(maxT-minT)/dt;
    if (!velocity) dt /= 2;
    cout << "XEF: " << xEf << endl;
    // Compute start position in Cartesian space
    auto [xE_start, _] = Ur5Direct(qES);
    cout << "xE_start: " << xE_start << endl;
    xEf(2)=xE_start(2);
    MatrixD6 tempTh;
    double total_time=((maxT-minT)/2==0) ? 1 : (maxT-minT)/2;
    double th_1=real(atan2(xEf(1), xEf(0)))-M_PI_2;
    Matrix16 qEF;
    qEF << th_1, qES(1), qES(2), qES(3), qES(4), qES(5);
    for(int i=0; i<num_points/2; i++) {
        double t=i*dt;
        Matrix16 thi;
        double interpolated_position=qES(0)+(t/total_time)*(qEF(0)-qES(0));
        thi(0)=interpolated_position;
        for(size_t j=1; j<NUM_JOINTS; j++) {
            thi(j)=qES(j);
        }
        printf("Time point %.2f: %f %f %f %f %f %f\n", (minT+i), thi(0), thi(1), thi(2), thi(3), thi(4), thi(5));
        tempTh.conservativeResize(tempTh.rows() + 1, NUM_JOINTS);
        tempTh.row(tempTh.rows() - 1) = thi;
    }
    Th->conservativeResize(Th->rows() + tempTh.rows(), NUM_JOINTS);
    Th->bottomRows(tempTh.rows()) = tempTh;
    qES=qEF;
    MatrixD6 end=Ur5Inverse(xEf, eul2rotm(phiEf));//Ur5InverseVerticalZ(xEf, eul2rotm(phiEf), th_1, qES(4), rot_gripper);
    if (!bestInverse(qES, end)) {
        cout << "No Inverse is admissible" << endl;
        return false;
    }
    minT=0;
    maxT=1;
    bool error=false;
    for(int i=0; i<num_points/2; i++) {
        double t=i*dt;
        Matrix16 thi;
        for(size_t j=0; j<NUM_JOINTS; j++) {
            double interpolated_position=qES(j)+(t/total_time)*(qEF(j)-qES(j));
            thi(j)=interpolated_position;
        }
        if (!checkAngles(&thi)) {
            cout << "TRAJECTORY ERROR" << endl;
            error = true;
        }
        printf("Time point %.2f: %f %f %f %f %f %f\n", (minT+i), thi(0), thi(1), thi(2), thi(3), thi(4), thi(5));
        tempTh.conservativeResize(tempTh.rows() + 1, NUM_JOINTS);
        tempTh.row(tempTh.rows() - 1) = thi;
    }
    return true;
    /*qES(1)=qEF(1);
    for (int i = 0; i < qEF.rows(); ++i) {
        qEF=end.row(i);
        MatrixD6 A;
        bool error = false;
        MatrixD6 tempTh;

        for (int j = 0; j < NUM_JOINTS; j++) {
            MatrixXd M(6, 6);
            M << 1, minT, pow(minT, 2), pow(minT, 3), pow(minT, 4), pow(minT, 5),
                0, 1, 2 * minT, 3 * pow(minT, 2), 4 * pow(minT, 3), 5 * pow(minT, 4),
                0, 0, 2, 6 * minT, 12 * pow(minT, 2), 20 * pow(minT, 3),
                1, maxT, pow(maxT, 2), pow(maxT, 3), pow(maxT, 4), pow(maxT, 5),
                0, 1, 2 * maxT, 3 * pow(maxT, 2), 4 * pow(maxT, 3), 5 * pow(maxT, 4),
                0, 0, 2, 6 * maxT, 12 * pow(maxT, 2), 20 * pow(maxT, 3);

            VectorXd b(6);
            b << qES(j), 0, 0, qEF(i, j), 0, 0;

            MatrixXd M_inv = M.inverse();
            VectorXd coeff = M_inv * b;
            A.conservativeResize(A.rows() + 1, Eigen::NoChange);
            A.row(A.rows() - 1) = coeff.transpose();
        }

        for (double t =minT; t < (maxT/2)+dt && !error; t += dt) {
              Matrix16 th;
              for (int k = 0; k < NUM_JOINTS; k++) {
                  th(k) = A(k, 0) + A(k, 1) * t + A(k, 2) * pow(t, 2) + A(k, 3) * pow(t, 3) + A(k, 4) * pow(t, 4) + A(k, 5) * pow(t, 5);
              }
              cout << "Time " << minT+1+t << ": " << th << endl;
              if (!checkAngles(&th)) {
                  cout << "TRAJECTORY ERROR" << endl;
                  error = true;
              }
              tempTh.conservativeResize(tempTh.rows() + 1, NUM_JOINTS);
              tempTh.row(tempTh.rows() - 1) = th;
          }

          if (!error) {
              Th->conservativeResize(Th->rows() + tempTh.rows(), NUM_JOINTS);
              Th->bottomRows(tempTh.rows()) = tempTh;
              return true;
          }
      }*/
    //return false;
}
