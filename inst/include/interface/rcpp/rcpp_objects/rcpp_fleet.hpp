/*
 * File:   rcpp_fleet.hpp
 *
 * Author: Matthew Supernaw
 * National Oceanic and Atmospheric Administration
 * National Marine Fisheries Service
 * Email: matthew.supernaw@noaa.gov
 *
 * Created on May 31, 2022 at 12:04 PM
 *
 * This File is part of the NOAA, National Marine Fisheries Service
 * Fisheries Integrated Modeling System project.
 *
 * This software is a "United States Government Work" under the terms of the
 * United States Copyright Act.  It was written as part of the author's official
 * duties as a United States Government employee and thus cannot be copyrighted.
 * This software is freely available to the public for use. The National Oceanic
 * And Atmospheric Administration and the U.S. Government have not placed any
 * restriction on its use or reproduction.  Although all reasonable efforts have
 * been taken to ensure the accuracy and reliability of the software and data,
 * the National Oceanic And Atmospheric Administration and the U.S. Government
 * do not and cannot warrant the performance or results that may be obtained by
 * using this  software or data. The National Oceanic And Atmospheric
 * Administration and the U.S. Government disclaim all warranties, express or
 * implied, including warranties of performance, merchantability or fitness
 * for any particular purpose.
 *
 * Please cite the author(s) in any work or product based on this material.
 *
 */
#ifndef FIMS_INTERFACE_RCPP_RCPP_OBJECTS_RCPP_FLEET_HPP
#define FIMS_INTERFACE_RCPP_RCPP_OBJECTS_RCPP_FLEET_HPP

#include "../../../population_dynamics/fleet/fleet.hpp"
#include "rcpp_interface_base.hpp"

class FleetInterface : public FIMSRcppInterfaceBase
{
    int observed_catch_data_id = -999;
    int observed_index_data_id = -999;
    int observed_agecomp_data_id = -999;
    int catch_likelihood_id = -999;
    int index_likelihood_id = -999;
    int agecomp_likelihood_id = -999;
    int selectivity_id = -999;

public:
    static uint32_t id_g;
    uint32_t id;

    FleetInterface()
    {
        this->id = FleetInterface::id_g++;
    }

    void SetAgeCompLikelihood(int agecomp_likelihood_id)
    {

        // Check if agecom likelihood has been set already
        if (this->agecomp_likelihood_id != -999)
        {
            warning("Age composition likelihood has been set already.");
            Rcout << "Now you are resetting age composition likelihood with age composition likelihood ID of "
                  << agecomp_likelihood_id << std::endl;
        }

        this->agecomp_likelihood_id = agecomp_likelihood_id;
    }

    void SetCatchLikelihood(int catch_likelihood_id)
    {
        // Check if catch likelihood has been set already
        if (this->catch_likelihood_id != -999)
        {
            warning("Catch likelihood has been set already.");
            Rcout << "Now you are resetting catch likelihood with catch likelihood ID of "
                  << catch_likelihood_id << std::endl;
        }

        this->catch_likelihood_id = catch_likelihood_id;
    }

    void SetIndexLikelihood(int index_likelihood_id)
    {

        // Check if index likelihood has been set already
        if (this->index_likelihood_id != -999)
        {
            warning("Index likelihood has been set already.");
            Rcout << "Now you are resetting index likelihood with index likelihood ID of "
                  << index_likelihood_id << std::endl;
        }

        this->index_likelihood_id = index_likelihood_id;
    }

    void SetObservedAgeCompData(int observed_agecomp_data_id)
    {

        // Check if observed age composition data have been set already
        if (this->observed_agecomp_data_id != -999)
        {
            warning("Observed age composition data have been set already.");
            Rcout << "Now you are resetting observed age composition data with observed age composition ID of "
                  << observed_agecomp_data_id << std::endl;
        }

        this->observed_agecomp_data_id = observed_agecomp_data_id;
    }

    void SetObservedIndexData(int observed_index_data_id)
    {

        // Check if observed index data have been set already
        if (this->observed_index_data_id != -999)
        {
            warning("Observed index data have been set already.");
            Rcout << "Now you are resetting observed index data with observed index data ID of "
                  << observed_index_data_id << std::endl;
        }

        this->observed_index_data_id = observed_index_data_id;
    }

    void SetObservedCatchData(int observed_catch_data_id)
    {

        // Check if observed catch data have been set already
        if (this->observed_catch_data_id != -999)
        {
            warning("Observed catch data have been set already.");
            Rcout << "Now you are resetting observed catch data with observed catch data ID of "
                  << observed_catch_data_id << std::endl;
        }

        this->observed_catch_data_id = observed_catch_data_id;
    }
    
    void SetSelectivity(int selectivity_id)
    {

        // Check if selectivity has been set already
        if (this->selectivity_id != -999)
        {

            warning("Selectivity has been set already.");
            Rcout << "Now you are resetting selectivity with selectivity ID of "
                  << selectivity_id << std::endl;
        }

        this->selectivity_id = selectivity_id;
    }

    virtual bool add_to_fims_tmb()
    {

        // base model
        std::shared_ptr<fims::Information<TMB_FIMS_REAL_TYPE>> d0 =
            fims::Information<TMB_FIMS_REAL_TYPE>::GetInstance();

        std::shared_ptr<fims::Fleet<TMB_FIMS_REAL_TYPE>> f0 =
            std::make_shared<fims::Fleet<TMB_FIMS_REAL_TYPE>>();

        f0->id = this->id;
        f0->agecomp_likelihood_id = this->agecomp_likelihood_id;
        f0->index_likelihood_id = this->index_likelihood_id;
        f0->catch_likelihood_id = this->catch_likelihood_id;
        f0->observed_agecomp_data_id = this->observed_agecomp_data_id;
        f0->observed_index_data_id = this->observed_index_data_id;
        f0->observed_catch_data_id = this->observed_catch_data_id;
        f0->selectivity_id = this->selectivity_id;

        // add to Information
        d0->fleets[f0->id] = f0;

        // 1st derivative model
        std::shared_ptr<fims::Information<TMB_FIMS_FIRST_ORDER>> d1 =
            fims::Information<TMB_FIMS_FIRST_ORDER>::GetInstance();

        std::shared_ptr<fims::Fleet<TMB_FIMS_FIRST_ORDER>> f1 =
            std::make_shared<fims::Fleet<TMB_FIMS_FIRST_ORDER>>();

        f1->id = this->id;
        f1->agecomp_likelihood_id = this->agecomp_likelihood_id;
        f1->index_likelihood_id = this->index_likelihood_id;
        f1->catch_likelihood_id = this->catch_likelihood_id;
        f1->observed_agecomp_data_id = this->observed_agecomp_data_id;
        f1->observed_index_data_id = this->observed_index_data_id;
        f1->observed_catch_data_id = this->observed_catch_data_id;
        f1->selectivity_id = this->selectivity_id;

        // add to Information
        d1->fleets[f1->id] = f1;

        // 2nd derivative model
        std::shared_ptr<fims::Information<TMB_FIMS_SECOND_ORDER>> d2 =
            fims::Information<TMB_FIMS_SECOND_ORDER>::GetInstance();

        std::shared_ptr<fims::Fleet<TMB_FIMS_SECOND_ORDER>> f2 =
            std::make_shared<fims::Fleet<TMB_FIMS_SECOND_ORDER>>();

        f2->id = this->id;
        f2->agecomp_likelihood_id = this->agecomp_likelihood_id;
        f2->index_likelihood_id = this->index_likelihood_id;
        f2->catch_likelihood_id = this->catch_likelihood_id;
        f2->observed_agecomp_data_id = this->observed_agecomp_data_id;
        f2->observed_index_data_id = this->observed_index_data_id;
        f2->observed_catch_data_id = this->observed_catch_data_id;
        f2->selectivity_id = this->selectivity_id;

        // add to Information
        d2->fleets[f2->id] = f2;

        // 3rd derivative model
        std::shared_ptr<fims::Information<TMB_FIMS_THIRD_ORDER>> d3 =
            fims::Information<TMB_FIMS_THIRD_ORDER>::GetInstance();

        std::shared_ptr<fims::Fleet<TMB_FIMS_THIRD_ORDER>> f3 =
            std::make_shared<fims::Fleet<TMB_FIMS_THIRD_ORDER>>();

        f3->id = this->id;
        f3->agecomp_likelihood_id = this->agecomp_likelihood_id;
        f3->index_likelihood_id = this->index_likelihood_id;
        f3->catch_likelihood_id = this->catch_likelihood_id;
        f3->observed_agecomp_data_id = this->observed_agecomp_data_id;
        f3->observed_index_data_id = this->observed_index_data_id;
        f3->observed_catch_data_id = this->observed_catch_data_id;
        f3->selectivity_id = this->selectivity_id;

        // add to Information
        d3->fleets[f3->id] = f3;
        return 0;
    }
};

uint32_t FleetInterface::id_g = 1;

#endif